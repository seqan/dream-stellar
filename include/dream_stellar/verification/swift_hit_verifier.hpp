#pragma once

#include <dream_stellar/stellar_database_segment.hpp>
#include <dream_stellar/stellar_query_segment.hpp>
#include <dream_stellar/options/eps_match_options.hpp>
#include <dream_stellar/options/verifier_options.hpp>
#include <dream_stellar/utils/stellar_kernel_runtime.hpp>

#include <type_traits> 

namespace dream_stellar {

template <typename TVerifierTag>
struct SwiftHitVerifier
{
    EPSMatchOptions eps_match_options;
    VerifierOptions verifier_options;

    template <typename TAlphabet, typename TDelta, typename TOnAlignmentResultFn>
    void verify(StellarDatabaseSegment<TAlphabet> const & databaseSegment,
                StellarQuerySegment<TAlphabet> const & querySegment,
                TDelta const delta,
                TOnAlignmentResultFn && onAlignmentResult,
                stellar_verification_time & verification_runtime)
    {
        static_assert(std::is_unsigned<TDelta>::value, "TDelta must be unsigned integral.");
        
        /* try to convert std::span back to String
        using TSegment = Segment<Segment<const std::span<TAlphabet const>, InfixSegment>, InfixSegment>; 
        TSegment finderSegment = databaseSegment.asFinderSegment();
        TSegment patternSegment = querySegment.asPatternSegment();

        using TString = String<TAlphabet>;
        TString host_infH;
        for (auto n : host(host(finderSegment)))
            appendValue(host_infH, n);
        Segment<const TString, InfixSegment> infH_seg{host_infH, 0, length(host_infH)};
        Segment<Segment<const TString, InfixSegment>, InfixSegment> infH(infH_seg, seqan2::beginPosition(finderSegment), seqan2::endPosition(finderSegment));

        TString host_infV;
        for (auto n : host(host(patternSegment)))
            appendValue(host_infV, n);
        Segment<const TString, InfixSegment> infV_seg{host_infV, 0, length(host_infV)};
        Segment<Segment<const TString, InfixSegment>, InfixSegment> infV(infV_seg, seqan2::beginPosition(patternSegment), seqan2::endPosition(patternSegment));
        */

        /*
        std::cout << "Swift hit verifier\n";
        for (auto n : databaseSegment.as_span())
            std::cout << seqan3::to_char(n._symbol);
        std::cout << '\n';

        for (auto n : querySegment.as_span())
            std::cout << seqan3::to_char(n._symbol);
        std::cout << '\n';
        */
       
        verifySwiftHit(
            databaseSegment.asFinderSegment(),
            querySegment.asPatternSegment(),
            (double)eps_match_options.epsilon,
            eps_match_options.minLength,
            verifier_options.xDrop,
            delta,
            onAlignmentResult,
            verification_runtime,
            TVerifierTag{});
    }
};

} // namespace dream_stellar
