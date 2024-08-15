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

#include <dream_stellar/stellar_database_segment.hpp>

#include <stellar/query_id_map.hpp>
#include <stellar/stellar.hpp>

namespace dream_stellar
{

template <typename TAlphabet, typename TId>
void _postproccessQueryMatches(bool const databaseStrand, uint64_t const & refLen,
                               StellarOptions const & options,
                               StringSet<QueryMatches<StellarMatch<String<TAlphabet> const, TId> > > & matches,
                               std::vector<size_t> & disabledQueryIDs)
{
    using TSequence = String<TAlphabet>;

    for (size_t queryID = 0; queryID < length(matches); ++queryID)
    {
        QueryMatches<StellarMatch<TSequence const, TId>> & queryMatches = value(matches, queryID);

        queryMatches.removeOverlapsAndCompactMatches(options.disableThresh,
                                                     /*compactThresh*/ 0,
                                                     options.minLength,
                                                     options.numMatches);

        if (queryMatches.disabled)
            disabledQueryIDs.push_back(queryID);
    }

    // adjust length for each matches of a single query (only for dna5 and rna5)
    // TODO: WHY? This seems like an arbitrary restriction
    if (databaseStrand || IsSameType<TAlphabet, Dna5>::VALUE || IsSameType<TAlphabet, Rna5>::VALUE)
        _postproccessLengthAdjustment(refLen, matches);
}

template <typename alphabet_t, typename sequence_reference_t = std::span<const alphabet_t>, typename id_t = std::string>
struct StellarLauncher
{
    template <typename visitor_fn_t>
    static constexpr stellar::StellarComputeStatistics _verificationMethodVisit(
        stellar::StellarVerificationMethod verificationMethod,
        visitor_fn_t && visitor_fn
    )
    {
        using namespace stellar;
        if (verificationMethod == StellarVerificationMethod{AllLocal{}})
            return visitor_fn(AllLocal());
        else if (verificationMethod == StellarVerificationMethod{BestLocal{}})
            return visitor_fn(BestLocal());
        else if (verificationMethod == StellarVerificationMethod{BandedGlobal{}})
            return visitor_fn(BandedGlobal());
        else if (verificationMethod == StellarVerificationMethod{BandedGlobalExtend{}})
            return visitor_fn(BandedGlobalExtend());
        return StellarComputeStatistics{};
    }

    static StellarComputeStatistics
    search_and_verify(
        jst::contrib::stellar_matcher<sequence_reference_t> & matcher, 
        sequence_reference_t database_segment,
        id_t const & databaseID,
        QueryIDMap<alphabet_t> const & queryIDMap,
        bool const databaseStrand,
        StellarOptions & localOptions, // localOptions.compactThresh is out-param
        stellar::stellar_kernel_runtime & strand_runtime,
        std::vector<QueryMatches<StellarMatch<std::vector<alphabet_t> const, id_t> > > & local_matches
    )
    {
        auto finder_callback = [&matcher, &localOptions](auto & finder)
        {
            bool has_next = find(finder, matcher);
            if (seqan2::length(finder.hits) > 0)
                seqan3::debug_stream << "FOUND MATCH\n";                     
        };

        // call operator() from seqan_pattern_base
        matcher(database_segment, localOptions.minRepeatLength, localOptions.maxRepeatPeriod, finder_callback);

        /*
        
        auto getQueryMatches = [&](auto const & pattern) -> QueryMatches<StellarMatch<sequence_reference_t const, id_t> > &
        {
            return value(localMatches, pattern.curSeqNo);
        };

        auto isPatternDisabled = [&](StellarSwiftPattern<TAlphabet> & pattern) -> bool {
            QueryMatches<StellarMatch<TSequence const, id_t> > & queryMatches = getQueryMatches(pattern);
            return queryMatches.disabled;
        };

        auto onAlignmentResult = [&](auto & alignment) -> bool {
            QueryMatches<StellarMatch<TSequence const, TId> > & queryMatches = getQueryMatches(localSwiftPattern);

            StellarMatch<TSequence const, TId> match(alignment, databaseID, databaseStrand);
            length(match);  // DEBUG: Contains assertion on clipping.

            // success
            return _insertMatch(
                queryMatches,
                match,
                localOptions.minLength,
                localOptions.disableThresh,
                // compactThresh is basically an output-parameter; will be updated in kernel and propagated back
                // outside of this function, the reason why StellarOptions can't be passed as const to this function.
                //!TODO: We might want to make this tied to the QueryMatches itself, as it should know then to consolidate
                // the matches
                localOptions.compactThresh,
                localOptions.numMatches
            );
        };

        // finder
        StellarSwiftFinder<TAlphabet> swiftFinder(databaseSegment.asInfixSegment(), localOptions.minRepeatLength, localOptions.maxRepeatPeriod);
        */

        matcher.make_finder(database_segment, localOptions.minRepeatLength, localOptions.maxRepeatPeriod);
        
        /*
        StellarComputeStatistics statistics = _verificationMethodVisit(
            localOptions.verificationMethod,
            [&]<typename TTag>(TTag tag) -> StellarComputeStatistics
            {
                SwiftHitVerifier<TTag> swiftVerifier
                {
                    STELLAR_DESIGNATED_INITIALIZER(.eps_match_options = , localOptions),
                    STELLAR_DESIGNATED_INITIALIZER(.verifier_options = , localOptions),
                };

                return _stellarKernel(swiftFinder, localSwiftPattern, swiftVerifier, isPatternDisabled, onAlignmentResult, strand_runtime);
            });

        */

        StellarComputeStatistics statistics{};
        return statistics;
    }
};

}   // namespace dream_stellar
