// -----------------------------------------------------------------------------------------------------
// Copyright (c) 2006-2021, Knut Reinert & Freie Universität Berlin
// Copyright (c) 2016-2021, Knut Reinert & MPI für molekulare Genetik
// This file may be used, modified and/or redistributed under the terms of the 3-clause BSD-License
// shipped with this file and also available at: https://github.com/seqan/seqan3/blob/master/LICENSE.md
// -----------------------------------------------------------------------------------------------------

/*!\file
 * \author Mitra Darvish <mitra.darvish AT fu-berlin.de>
 * \brief Edited by Evelin Aasna based on seqan3::views::minimiser_hash.
 */

#pragma once

#include <seqan3/alphabet/views/complement.hpp>
#include <seqan3/core/detail/strong_type.hpp>
#include <seqan3/search/views/kmer_hash.hpp>
#include <indexed_minimiser.hpp>

namespace sliding_window
{
//!\brief strong_type for seed.
//!\ingroup search_views
struct seed : seqan3::detail::strong_type<uint64_t, seed>
{
    using seqan3::detail::strong_type<uint64_t, seed>::strong_type;
};

//!\brief strong_type for the window_size.
//!\ingroup search_views
struct window_size : seqan3::detail::strong_type<uint32_t, window_size>
{
    using seqan3::detail::strong_type<uint32_t, window_size>::strong_type;
};

//!\brief seqan3::views::minimiser_hash's range adaptor object type (non-closure).
//!\ingroup search_views
//
// The adaptor should:
// 1. facilitate piping behavior
// 2. allow for creation of view objects
//
struct indexed_minimiser_hash_fn
{
    /*!\brief Store the shape and the window size and return a range adaptor closure object.
    * \param[in] shape       The seqan3::shape to use for hashing.
    * \param[in] window_size The windows size to use.
    * \throws std::invalid_argument if the size of the shape is greater than the `window_size`.
    * \returns               A range of converted elements.
    */
    constexpr auto operator()(seqan3::shape const & shape, window_size const window_size) const
    {
        return seqan3::detail::adaptor_from_functor{*this, shape, window_size};
    }

    /*!\brief Store the shape, the window size and the seed and return a range adaptor closure object.
    * \param[in] shape       The seqan3::shape to use for hashing.
    * \param[in] window_size The size of the window.
    * \param[in] seed        The seed to use.
    * \throws std::invalid_argument if the size of the shape is greater than the `window_size`.
    * \returns               A range of converted elements.
    */
    constexpr auto operator()(seqan3::shape const & shape, window_size const window_size, seed const seed) const
    {
        return seqan3::detail::adaptor_from_functor{*this, shape, window_size, seed};
    }

    /*!\brief Call the view's constructor with the underlying view, a seqan3::shape and a window size as argument.
     * \param[in] urange      The input range to process. Must model std::ranges::viewable_range and the reference type
     *                        of the range must model seqan3::semialphabet.
     * \param[in] shape       The seqan3::shape to use for hashing.
     * \param[in] window_size The size of the window.
     * \param[in] seed        The seed to use.
     * \throws std::invalid_argument if the size of the shape is greater than the `window_size`.
     * \returns               A range of converted elements.
     */
    template <std::ranges::range urng_t>
    constexpr auto operator()(urng_t && urange,
                              seqan3::shape const & shape,
                              window_size const window_size,
                              seed const seed = seed{0x8F3F73B5CF1C9ADE}) const
    {
        static_assert(std::ranges::viewable_range<urng_t>,
            "The range parameter to views::minimiser_hash cannot be a temporary of a non-view range.");
        static_assert(std::ranges::forward_range<urng_t>,
            "The range parameter to views::minimiser_hash must model std::ranges::forward_range.");
        static_assert(seqan3::semialphabet<std::ranges::range_reference_t<urng_t>>,
            "The range parameter to views::minimiser_hash must be over elements of seqan3::semialphabet.");

        if (shape.size() > window_size.get())
            throw std::invalid_argument{"The size of the shape cannot be greater than the window size."};

        auto forward_strand = std::forward<urng_t>(urange) | seqan3::views::kmer_hash(shape)
                                                           | std::views::transform([seed] (uint64_t i)
                                                                                  {return i ^ seed.get();});

        auto reverse_strand = std::forward<urng_t>(urange) | seqan3::views::complement
                                                           | std::views::reverse
                                                           | seqan3::views::kmer_hash(shape)
                                                           | std::views::transform([seed] (uint64_t i)
                                                                                  {return i ^ seed.get();})
                                                           | std::views::reverse;

        return indexed_minimiser_view(forward_strand, reverse_strand, window_size.get() - shape.size() + 1);
    }
    
};

inline constexpr auto indexed_minimiser_hash = indexed_minimiser_hash_fn{};

} // namespace sliding_window

