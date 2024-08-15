#pragma once

// can we replace this include by some forwards?
// needed for seqan2::indexText, seqan2::needle
#include <seqan/index.h>

#include <dream_stellar/stellar_sequence_segment.hpp>

namespace dream_stellar
{

template <typename TAlphabet>
template <typename TSwiftPattern>
StellarQuerySegment<TAlphabet>
StellarQuerySegment<TAlphabet>::fromPatternMatch(TSwiftPattern const & swiftPattern)
{
    size_t const queryID = swiftPattern.curSeqNo;
    auto const & queryInfix = seqan2::getSequenceByNo(queryID, seqan2::indexText(seqan2::needle(swiftPattern)));
    static_assert(std::is_same_v<decltype(queryInfix), TInfixSegment const &>);
    auto const & underlyingQuery = host(queryInfix);
    static_assert(std::is_same_v<decltype(underlyingQuery), seqan2::String<TAlphabet> const &>);
    auto const queryInfixInfix = seqan2::infix(swiftPattern, queryInfix);

    return {underlyingQuery, seqan2::beginPosition(queryInfixInfix), seqan2::endPosition(queryInfixInfix)};
}

} // namespace dream_stellar
