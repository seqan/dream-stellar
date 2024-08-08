// -----------------------------------------------------------------------------------------------------
// Copyright (c) 2006-2021, Knut Reinert & Freie Universität Berlin
// Copyright (c) 2016-2021, Knut Reinert & MPI für molekulare Genetik
// This file may be used, modified and/or redistributed under the terms of the 3-clause BSD-License
// shipped with this file and also available at: https://github.com/seqan/seqan3/blob/master/LICENSE.md
// -----------------------------------------------------------------------------------------------------

/*!\file
 * \brief Provides an adapter to make the SWIFT algorithm work with std views.
 * \author Rene Rahn <rene.rahn AT fu-berlin.de>
 */

#pragma once

#include <valik/shared.hpp>

#include <seqan/basic/alphabet_simple_type.h>
#include <utilities/alphabet_wrapper/seqan/alphabet.hpp>
#include <utilities/alphabet_wrapper/seqan/container_adapter.hpp>
#include <utilities/alphabet_wrapper/matcher/seqan_pattern_base.hpp>

namespace jst::contrib
{
    using namespace seqan2;

    template <typename needle_t>
    using compatible_needle_type = jst::contrib::seqan_container_t<std::views::all_t<needle_t &>>;

    template <typename needle_t>
    using multi_needle_type = seqan2::StringSet<compatible_needle_type<needle_t>>;

    template <typename needle_t>
    using qgram_shape_type = seqan2::Shape<std::ranges::range_value_t<compatible_needle_type<needle_t>>, seqan2::SimpleShape>;

    template <typename needle_t>
    using index_type = seqan2::Index<multi_needle_type<needle_t>, seqan2::IndexQGram<qgram_shape_type<needle_t>, seqan2::OpenAddressing>>;

    template <std::ranges::random_access_range needle_t>
    class stellar_matcher : public seqan_pattern_base<stellar_matcher<needle_t>>
    {
    private:

        using base_t = seqan_pattern_base<stellar_matcher<needle_t>>;

        friend base_t;

        using finder_spec_type = seqan2::Swift<seqan2::SwiftLocal>;
        using pattern_type = seqan2::Pattern<index_type<needle_t>, finder_spec_type>;

        multi_needle_type<needle_t> _multi_needle{};
        index_type<needle_t> _needle_index{_multi_needle};
        pattern_type _pattern{_needle_index};
        size_t _kmer_size{};
        double _kmer_abundance_cut{};
        double _error_rate{};
        unsigned _min_length{};

    public:

        stellar_matcher() = delete;
        template <std::ranges::viewable_range _needle_t>
            requires (!std::same_as<_needle_t, stellar_matcher> &&
                       std::constructible_from<compatible_needle_type<needle_t>, _needle_t>)
        explicit stellar_matcher(_needle_t && needle, valik::search_arguments const & arguments) :
            _kmer_size{arguments.shape_size}, _kmer_abundance_cut{arguments.qgramAbundanceCut}, 
            _error_rate{arguments.error_rate}, _min_length{arguments.minLength}
        {
            appendValue(getFibre(_needle_index, seqan2::QGramText{}),
                        jst::contrib::make_seqan_container(std::views::all((_needle_t &&) needle)));
            // like line 108 in stellar_index.hpp
            resize(indexShape(_needle_index), _kmer_size);
            cargo(_needle_index).abundanceCut = _kmer_abundance_cut;
            _patternInit(_pattern, _error_rate, _min_length);
        }

        template <std::ranges::viewable_range _multi_needle_t>
            requires (!std::same_as<_multi_needle_t, stellar_matcher> &&
                       std::constructible_from<compatible_needle_type<needle_t>,
                                               std::views::all_t<std::ranges::range_reference_t<_multi_needle_t>>>)
        explicit stellar_matcher(_multi_needle_t && multi_needle, valik::search_arguments const & arguments) :
            _kmer_size{arguments.shape_size}, _kmer_abundance_cut{arguments.qgramAbundanceCut}, 
            _error_rate{arguments.error_rate}, _min_length{arguments.minLength}
        {
            for (auto && needle : multi_needle)
            {
                appendValue(getFibre(_needle_index, seqan2::QGramText{}),
                            jst::contrib::make_seqan_container(std::views::all((decltype(needle) &&) needle)));

                // debug                
                // seqan3::debug_stream << "Appending fibre \n" << needle << '\n';
            }


            // like line 108 in stellar_index.hpp
            resize(indexShape(_needle_index), _kmer_size);
            cargo(_needle_index).abundanceCut = _kmer_abundance_cut;
            _patternInit(_pattern, _error_rate, _min_length);
        }

        constexpr auto position() const noexcept {
            return seqan2::position(_pattern);
        }
        
        template <typename haystack_t>
        constexpr auto make_finder(haystack_t & haystack, size_t const minRepeatLength, size_t const maxRepeatPeriod) const noexcept
        {
            return seqan2::Finder<haystack_t, finder_spec_type>{haystack, minRepeatLength, maxRepeatPeriod};
        }

    private:
        constexpr stellar_matcher & get_pattern() noexcept {
            return *this;
        }

        constexpr auto custom_find_arguments() const noexcept {
            return std::tuple{_error_rate, _min_length};
        }

        constexpr friend std::size_t tag_invoke(std::tag_t<window_size>, stellar_matcher const & me) noexcept {
            return length(getFibre(needle(me._pattern), seqan2::QGramShape{}));
        }

    /////////////////////////////////////////////////////////////////////////////////
        template <typename haystack_t>
        constexpr bool initialise(seqan2::Finder<haystack_t, finder_spec_type> & finder,
                                  pattern_type & pattern)
        {
            pattern.finderLength = std::ranges::size(haystack(finder));
            seqan2::_patternInit(pattern, _error_rate, _min_length);
            seqan2::_finderSetNonEmpty(finder);
            finder.dotPos = 100000;
            finder.dotPos2 = 10 * finder.dotPos;

            if (!seqan2::_firstNonRepeatRange(finder, pattern))
                return false;

            if (seqan2::_swiftMultiProcessQGram(finder, pattern, seqan2::hash(pattern.shape, hostIterator(hostIterator(finder)))))
                seqan2::_copySwiftHit(finder, pattern);

            return true;
        }

        // declare and define a non-member friend function
        template <typename haystack_t, typename ...args_t>
        friend bool find(seqan2::Finder<haystack_t, finder_spec_type> & finder,
                         stellar_matcher & matcher,
                         args_t && ...args)
        {
            pattern_type & pattern = matcher._pattern;
            if (empty(finder)) {
                return matcher.initialise(finder, pattern);
            }

            // all previous matches reported -> search new ones
            clear(finder.hits);

            // are we at the end of the text?
            if (seqan2::atEnd(finder) && finder.curRepeat == finder.endRepeat)
            {
                finder.curHit = finder.endHit;
                return false;
            }

            do
            {
                if (pattern.params.printDots) seqan2::_printDots(finder);
                if (seqan2::atEnd(++finder))
                {
                    if (!seqan2::_nextNonRepeatRange(finder, pattern))
                    {
                        if(seqan2::_swiftMultiFlushBuckets(finder, pattern))
                        {
                            seqan2::_copySwiftHit(finder, pattern);
                            return true;
                        }
                        else
                            return false;
                    }
                    seqan2::hash(pattern.shape, seqan2::hostIterator(seqan2::hostIterator(finder)));
                }
                else
                {
                    ++finder.curPos;
                    seqan2::hashNext(pattern.shape, seqan2::hostIterator(seqan2::hostIterator(finder)));
                }

                if (seqan2::_swiftMultiProcessQGram(finder, pattern, seqan2::value(pattern.shape)))
                {
                    seqan2::_copySwiftHit(finder, pattern);
                    return true;
                }

            } while (true);
        }
    };

    /////////////////////////////////////////////////////////////////////////////////

    template <std::ranges::viewable_range needle_t>
    stellar_matcher(needle_t &&) -> stellar_matcher<std::views::all_t<needle_t>>;

    template <std::ranges::viewable_range needle_t>
    stellar_matcher(needle_t &&, double) -> stellar_matcher<std::views::all_t<needle_t>>;

    template <std::ranges::viewable_range multi_needle_t>
        requires std::ranges::random_access_range<std::ranges::range_reference_t<multi_needle_t>>
    stellar_matcher(multi_needle_t &&) -> stellar_matcher<std::views::all_t<std::ranges::range_reference_t<multi_needle_t>>>;

    template <std::ranges::viewable_range multi_needle_t>
        requires std::ranges::random_access_range<std::ranges::range_reference_t<multi_needle_t>>
    stellar_matcher(multi_needle_t &&, double) -> stellar_matcher<std::views::all_t<std::ranges::range_reference_t<multi_needle_t>>>;

}  // namespace jst::contrib

namespace seqan2 {

using needle_t = std::vector<seqan2::alphabet_adaptor<seqan3::dna4>>;

template <>
struct Cargo<::jst::contrib::index_type<needle_t>>
{
    typedef struct
    {
        double      abundanceCut;
    } Type;
};

} // namespace seqan2
