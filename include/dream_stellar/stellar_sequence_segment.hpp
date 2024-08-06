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

#include <seqan/sequence.h>

namespace dream_stellar
{

template <typename TAlphabet>
struct StellarSequenceSegment
{
    using TString = seqan2::String<TAlphabet>;
    using TInfixSegment = seqan2::Segment<TString const, seqan2::InfixSegment>;

    StellarSequenceSegment() = default;

    template <typename TOtherString, typename = std::enable_if_t< std::is_same_v<TString, TOtherString> > >
    StellarSequenceSegment(
        TOtherString const & sequence,
        size_t const beginPosition,
        size_t const endPosition)
        : _sequenceSegment{sequence, beginPosition, endPosition}
    {}

    seqan2::String<TAlphabet> const & underlyingSequence() const &
    {
        return host(_sequenceSegment);
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

    TInfixSegment asInfixSegment() const
    {
        return _sequenceSegment;
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
