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

template <typename TAlphabet, typename TId = CharString>
struct StellarLauncher
{
    template <typename visitor_fn_t>
    static constexpr StellarComputeStatistics _verificationMethodVisit(
        StellarVerificationMethod verificationMethod,
        visitor_fn_t && visitor_fn
    )
    {
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
        dream_stellar::StellarDatabaseSegment<TAlphabet> const databaseSegment,
        TId const & databaseID,
        QueryIDMap<TAlphabet> const & queryIDMap,
        bool const databaseStrand,
        StellarOptions & localOptions, // localOptions.compactThresh is out-param
        StellarSwiftPattern<TAlphabet> & localSwiftPattern,
        stellar::stellar_kernel_runtime & strand_runtime,
        StringSet<QueryMatches<StellarMatch<String<TAlphabet> const, TId> > > & localMatches
    )
    {
        using TSequence = String<TAlphabet>;

        auto getQueryMatches = [&](auto const & pattern) -> QueryMatches<StellarMatch<TSequence const, TId> > &
        {
            return value(localMatches, pattern.curSeqNo);
        };

        auto isPatternDisabled = [&](StellarSwiftPattern<TAlphabet> & pattern) -> bool {
            QueryMatches<StellarMatch<TSequence const, TId> > & queryMatches = getQueryMatches(pattern);
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
        
        //!TODO: replace matcher
        // jst::contrib::stellar_matcher matcher(queries, localOptions.minRepeatLength, localOptions.maxRepeatPeriod);
        // matcher.make_finder(databaseSegment);
        
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

        return statistics;
    }
};

}   // namespace dream_stellar
