#pragma once

#include <dream_stellar/stellar_sequence_segment.hpp>

namespace dream_stellar
{

template <typename alphabet_t>
struct StellarQuerySegment : public StellarSequenceSegment<alphabet_t>
{
    using TBase = StellarSequenceSegment<alphabet_t>;

    using typename TBase::TInfixSegment;
    using TNestedPatternSegment = seqan2::Segment<TInfixSegment, seqan2::InfixSegment>;

    using TBase::TBase; // import constructor

    std::span<alphabet_t> const & underlyingQuery() const &
    {
        return this->underlyingSequence();
    }

    TNestedPatternSegment asPatternSegment() const
    {
        std::span<alphabet_t> const & _query = underlyingQuery();
        auto patternInfix = this->asInfixSegment();

        TInfixSegment const patternInfixSeq = infix(_query, 0, length(_query));
        return {
            patternInfixSeq,
            seqan2::beginPosition(patternInfix) - seqan2::beginPosition(patternInfixSeq),
            seqan2::endPosition(patternInfix) - seqan2::beginPosition(patternInfixSeq)
        };
    }
};

} // namespace dream_stellar
