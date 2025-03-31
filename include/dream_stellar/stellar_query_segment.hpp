
#pragma once

#include <dream_stellar/stellar_sequence_segment.hpp>

namespace dream_stellar
{

template <typename TAlphabet>
struct StellarQuerySegment : public StellarSequenceSegment<TAlphabet>
{
    using TBase = StellarSequenceSegment<TAlphabet>;

    using typename TBase::TInfixSegment;
    using TNestedPatternSegment = seqan2::Segment<TInfixSegment, seqan2::InfixSegment>;

    using TBase::TBase; // import constructor

    template <typename TSwiftPattern>
    static StellarQuerySegment<TAlphabet> fromPatternMatch(TSwiftPattern const & swiftPattern);

    seqan2::String<TAlphabet> const & underlyingQuery() const &
    {
        return this->underlyingSequence();
    }

    TNestedPatternSegment asPatternSegment() const
    {
        seqan2::String<TAlphabet> const & _query = underlyingQuery();
        auto patternInfix = this->asInfixSegment();

        TInfixSegment const patternInfixSeq = infix(_query, 0, length(_query));

        assert(seqan2::beginPosition(patternInfixSeq) == 0UL);
        return {
            patternInfixSeq,
            seqan2::beginPosition(patternInfix),
            seqan2::endPosition(patternInfix)
        };
    }
};

} // namespace dream_stellar
