#pragma once

#include <seqan/sequence.h>

namespace dream_stellar
{

template <typename alphabet_t>
struct StellarSequenceSegment
{
    using sequence_reference_t = std::span<const alphabet_t>;
    using TInfixSegment = seqan2::Segment<sequence_reference_t const, seqan2::InfixSegment>;

    StellarSequenceSegment() = default;

    StellarSequenceSegment(
        sequence_reference_t const & sequence,
        size_t const beginPosition,
        size_t const endPosition)
        : _sequenceSegment{sequence, beginPosition, endPosition}
    {}

    // do not allow temporaries
    StellarSequenceSegment(
        sequence_reference_t && sequence,
        size_t const beginPosition,
        size_t const endPosition) = delete;

    sequence_reference_t const & underlyingSequence() const
    {
        assert(_sequenceSegment.data_host);
        return *(_sequenceSegment.data_host);
    }

    size_t beginPosition() const
    {
        return seqan2::beginPosition(_sequenceSegment);
    }

    size_t endPosition() const
    {
        return seqan2::endPosition(_sequenceSegment);
    }

    std::pair<size_t, size_t> interval() const
    {
        return {beginPosition(), endPosition()};
    }

    size_t size() const
    {
        assert(endPosition() >= beginPosition());
        return endPosition() - beginPosition();
    }

    TInfixSegment const & asInfixSegment() const
    {
        return _sequenceSegment;
    }

    std::span<const alphabet_t> as_span() const
    {
        return this->underlyingSequence().subspan(this->beginPosition() /* offset */, 
                                                  this->endPosition() - this->beginPosition() /* count */);
    }

    friend bool operator<(StellarSequenceSegment const & s1, StellarSequenceSegment const & s2) { return s1.compare_three_way(s2) < 0; }
    friend bool operator<=(StellarSequenceSegment const & s1, StellarSequenceSegment const & s2) { return s1.compare_three_way(s2) <= 0; }
    friend bool operator==(StellarSequenceSegment const & s1, StellarSequenceSegment const & s2) { return s1.compare_three_way(s2) == 0; }
    friend bool operator!=(StellarSequenceSegment const & s1, StellarSequenceSegment const & s2) { return s1.compare_three_way(s2) != 0; }
    friend bool operator>(StellarSequenceSegment const & s1, StellarSequenceSegment const & s2) { return s1.compare_three_way(s2) > 0; }
    friend bool operator>=(StellarSequenceSegment const & s1, StellarSequenceSegment const & s2) { return s1.compare_three_way(s2) >= 0; }

private:

    std::ptrdiff_t compare_three_way(StellarSequenceSegment const & otherSegment) const
    {
        std::ptrdiff_t diff = std::addressof(this->underlyingSequence())
                            - std::addressof(otherSegment.underlyingSequence());

        if (diff != 0)
            return diff;

        diff = static_cast<std::ptrdiff_t>(this->beginPosition()) - static_cast<std::ptrdiff_t>(otherSegment.beginPosition());

        if (diff != 0)
            return diff;

        diff = static_cast<std::ptrdiff_t>(this->endPosition()) - static_cast<std::ptrdiff_t>(otherSegment.endPosition());
        return diff;
    }

    TInfixSegment _sequenceSegment;
};

} // namespace dream_stellar
