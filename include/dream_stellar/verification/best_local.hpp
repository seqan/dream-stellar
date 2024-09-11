
#pragma once

#include <dream_stellar/verification/detail/all_or_best_local.hpp>

namespace dream_stellar
{

///////////////////////////////////////////////////////////////////////////////
// Conducts banded local alignment on swift hit (= computes eps-cores),
//  splits eps-cores at X-drops, and calls _extendAndExtract for extension of eps-cores
template<typename TSequence, typename TEpsilon, typename TSize, typename TDrop, typename TDelta,
         typename TOnAlignmentResultFn>
void
verifySwiftHit(Segment<Segment<TSequence const, InfixSegment>, InfixSegment> const & infH,
               Segment<Segment<TSequence const, InfixSegment>, InfixSegment> const & infV,
               /*double*/ TEpsilon const eps,
               /*int*/ TSize const minLength,
               /*double*/ TDrop const xDrop,
               /*unsigned_integral*/ TDelta const delta,
               TOnAlignmentResultFn && onAlignmentResult,
               stellar_verification_time & verification_runtime,
               BestLocal) {

    // true == best local match
    allOrBestLocal(infH, infV, eps, minLength, xDrop, delta, onAlignmentResult, verification_runtime, std::true_type{});
}

} // namespace dream_stellar
