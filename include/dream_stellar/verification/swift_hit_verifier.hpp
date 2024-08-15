#pragma once

#include <dream_stellar/stellar_database_segment.hpp>
#include <dream_stellar/stellar_query_segment.hpp>
#include <dream_stellar/options/eps_match_options.hpp>
#include <dream_stellar/options/verifier_options.hpp>
#include <dream_stellar/utils/stellar_kernel_runtime.hpp>

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
