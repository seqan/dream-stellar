#pragma once

#include <dream_stellar/query_id_map.hpp>
#include <dream_stellar/stellar_database_segment.hpp>
#include <dream_stellar/stellar.hpp>

namespace dream_stellar
{

template <typename TAlphabet, typename TId>
void _postprocessQueryMatches(bool const databaseStrand, uint64_t const & refLen,
                               StellarOptions const & options,
                               std::vector<QueryMatches<StellarMatch<std::span<TAlphabet const> const, TId> > > & matches,
                               std::vector<size_t> & disabledQueryIDs)
{
    using TSequence = std::span<TAlphabet const>;

    for (size_t queryID = 0; queryID < matches.size(); ++queryID)
    {
        if (matches.size() <= queryID)
            throw std::runtime_error("Query ID=" + std::to_string(queryID) + " out of range [0;" + std::to_string(matches.size() - 1) + "]");

        QueryMatches<StellarMatch<TSequence const, TId>> & queryMatches = matches[queryID];

        queryMatches.removeOverlapsAndCompactMatches(options.disableThresh,
                                                     /*compactThresh*/ 0,
                                                     options.minLength,
                                                     options.numMatches);

        if (queryMatches.disabled)
            disabledQueryIDs.push_back(queryID);
    }
}

template <typename alphabet_t, typename sequence_reference_t = std::span<const alphabet_t>, typename id_t = std::string>
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
        return StellarComputeStatistics{};
    }

    static StellarComputeStatistics
    search_and_verify(
        jst::contrib::stellar_matcher<sequence_reference_t> & matcher, 
        StellarDatabaseSegment<const alphabet_t> database_segment,
        id_t const & databaseID,
        query_id_map<alphabet_t> const & query_dict,
        bool const databaseStrand,
        StellarOptions & localOptions, // localOptions.compactThresh is out-param
        stellar_kernel_runtime & strand_runtime,
        std::vector<QueryMatches<StellarMatch<const sequence_reference_t, id_t> > > & local_matches
    )
    {        
        auto getQueryMatches = [&](jst::contrib::stellar_matcher<sequence_reference_t> const & stellar_matcher) 
                               -> QueryMatches<StellarMatch<sequence_reference_t const, id_t> > &
        {
            if (local_matches.size() < stellar_matcher.curSeqNo())
                throw std::runtime_error{"Pattern defined incorrectly. Out of sequence range."};
            return local_matches[stellar_matcher.curSeqNo()];
        };

        auto isPatternDisabled = [&](jst::contrib::stellar_matcher<sequence_reference_t> const & matcher) -> bool 
        {
            QueryMatches<StellarMatch<sequence_reference_t const, id_t> > & queryMatches = getQueryMatches(matcher);
            return queryMatches.disabled;
        };

        auto onAlignmentResult = [&](auto & alignment) -> bool {
            QueryMatches<StellarMatch<sequence_reference_t const, id_t> > & queryMatches = getQueryMatches(matcher);
            StellarMatch<seqan2::String<seqan2::alphabet_adaptor<seqan3::dna4>> const, id_t> match(alignment, databaseID, databaseStrand);
            length(match);  // DEBUG: Contains assertion on clipping.

            // success
            return queryMatches.insertMatch(
                match,
                localOptions.minLength,
                localOptions.disableThresh,
                localOptions.compactThresh, /* out-parameter */
                localOptions.numMatches
            );
        };

        StellarComputeStatistics statistics = _verificationMethodVisit(
            localOptions.verificationMethod,
            [&]<typename TTag>(TTag tag) -> StellarComputeStatistics
            {
                SwiftHitVerifier<TTag> swiftVerifier
                {
                    STELLAR_DESIGNATED_INITIALIZER(.eps_match_options = , localOptions),
                    STELLAR_DESIGNATED_INITIALIZER(.verifier_options = , localOptions),
                };

                return _stellarKernel(matcher, database_segment, query_dict, localOptions, swiftVerifier, isPatternDisabled, onAlignmentResult, strand_runtime);
            });
        return statistics;
    }
};

}   // namespace dream_stellar
