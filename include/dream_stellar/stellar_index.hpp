// ==========================================================================
//                    STELLAR - SwifT Exact LocaL AligneR
//                   http://www.seqan.de/projects/stellar/
// ==========================================================================
// Copyright (C) 2010-2012 by Birte Kehr
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your options) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// ==========================================================================
// Author: Birte Kehr <birte.kehr@fu-berlin.de>
// ==========================================================================
#pragma once

#include <seqan/index.h>

#include <span>

#include <utilities/alphabet_wrapper/matcher/stellar_matcher.hpp>
#include <stellar/options/index_options.hpp>

namespace dream_stellar
{
using namespace seqan2;
using namespace stellar;

template <typename TAlphabet, typename TString = String<TAlphabet>, typename TInfixSegment = seqan2::Segment<TString const, seqan2::InfixSegment>>
using StellarQGramStringSet = StringSet<TInfixSegment, Owner<> >;

template <typename TAlphabet>
using StellarQGramIndex = Index<StellarQGramStringSet<TAlphabet> const, IndexQGram<SimpleShape, OpenAddressing> >;

template <typename TAlphabet>
using StellarSwiftPattern = Pattern<StellarQGramIndex<TAlphabet>, Swift<SwiftLocal> >;

template <typename TAlphabet>
using StellarSwiftFinder = Finder<Segment<String<TAlphabet> const, InfixSegment> const, Swift<SwiftLocal> >;

template <typename TAlphabet>
struct StellarIndex
{
    using TSequence = seqan2::String<TAlphabet>;
    using TInfixSegment = seqan2::Segment<seqan2::String<TAlphabet> const, seqan2::InfixSegment>;
    using TQGramStringSet = StellarQGramStringSet<TAlphabet>;

    template <typename TSpec>
    StellarIndex(StringSet<TSequence, TSpec> const & queries, IndexOptions const & options)
        : StellarIndex{convertImplStringSet(queries), options}
    {}

    StellarIndex(StringSet<TInfixSegment> const & queries, IndexOptions const & options)
        : StellarIndex{convertSegmentStringSet(queries), options}
    {}

    StellarIndex(std::span<TInfixSegment> const & queries, IndexOptions const & options)
        : StellarIndex{convertImplSpan(queries), options}
    {}

    StellarIndex() = delete;
    StellarIndex(StellarIndex &&) = delete;
    StellarIndex(StellarIndex const &) = delete;
    StellarIndex & operator=(StellarIndex &&) = delete;
    StellarIndex & operator=(StellarIndex const &) = delete;

    void construct()
    {
        indexRequire(qgramIndex, QGramSADir());
    }

    StellarSwiftPattern<TAlphabet> createSwiftPattern()
    {
        return {qgramIndex};
    }

    static StellarQGramIndex<TAlphabet> & qgramIndexFromPattern(StellarSwiftPattern<TAlphabet> & pattern)
    {
        return host(pattern);
    }

    static TQGramStringSet const & sequencesFromPattern(StellarSwiftPattern<TAlphabet> & pattern)
    {
        return sequencesFromQGramIndex(qgramIndexFromPattern(pattern));
    }

    static TQGramStringSet const & sequencesFromQGramIndex(StellarQGramIndex<TAlphabet> & index)
    {
        return indexText(index);
    }

    TQGramStringSet const dependentQueries;
    StellarQGramIndex<TAlphabet> qgramIndex;

private:
    template <typename TOtherQGramStringSet, typename = std::enable_if_t<std::is_same_v<TOtherQGramStringSet, TQGramStringSet>>>
    StellarIndex(TOtherQGramStringSet && queries, IndexOptions const & options)
        : dependentQueries{std::forward<TOtherQGramStringSet>(queries)}, qgramIndex{dependentQueries}
    {
        resize(indexShape(qgramIndex), options.qGram);
        cargo(qgramIndex).abundanceCut = options.qgramAbundanceCut;
    }

    template <typename TSpec>
    static TQGramStringSet convertImplStringSet(StringSet<TSequence, TSpec> const & queries)
    {
        TQGramStringSet dependentQueries;
        for (TSequence const & query: queries)
            seqan2::appendValue(dependentQueries, seqan2::infix(query, 0, seqan2::length(query)));

        return dependentQueries;
    }

    static TQGramStringSet convertSegmentStringSet(StringSet<TInfixSegment> const & queries)
    {
        TQGramStringSet dependentQueries = queries;
        return dependentQueries;
    }

    static TQGramStringSet convertImplSpan(std::span<TInfixSegment> const & queries)
    {
        TQGramStringSet dependentQueries;
        for (TInfixSegment const & query: queries)
            seqan2::appendValue(dependentQueries, query);

        return dependentQueries;
    }
};

} // namespace dream_stellar
