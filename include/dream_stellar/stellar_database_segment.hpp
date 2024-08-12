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

#include <seqan/seq_io.h>

#include <dream_stellar/stellar_sequence_segment.hpp>
#include <stellar/stellar_types.hpp>

namespace dream_stellar
{

using namespace seqan2;

template <typename TAlphabet>
struct StellarDatabaseSegment : public StellarSequenceSegment<TAlphabet>
{
    using TBase = StellarSequenceSegment<TAlphabet>;

    using typename TBase::TInfixSegment;
    using TNestedFinderSegment = seqan2::Segment<TInfixSegment, seqan2::InfixSegment>;

    using TBase::TBase; // import constructor

    static StellarDatabaseSegment<TAlphabet> fromFinderMatch(TInfixSegment const & finderMatch)
    {
        seqan2::String<TAlphabet> const & underlyingDatabase = host(finderMatch);
        return {underlyingDatabase, seqan2::beginPosition(finderMatch), seqan2::endPosition(finderMatch)};
    }

    seqan2::String<TAlphabet> const & underlyingDatabase() const &
    {
        return this->underlyingSequence();
    }

    TNestedFinderSegment asFinderSegment() const
    {
        seqan2::String<TAlphabet> const & _database = underlyingDatabase();
        auto finderInfix = this->asInfixSegment();

        TInfixSegment const finderInfixSeq = infix(_database, 0, length(_database));
        TNestedFinderSegment finderSegment(finderInfixSeq,
            seqan2::beginPosition(finderInfix) - seqan2::beginPosition(_database),
            seqan2::endPosition(finderInfix) - seqan2::beginPosition(_database));
        return finderSegment;
    }
};

//!TODO: could not convert ‘span<alphabet_adaptor<[...]>,[...]>’ to ‘span<alphabet_adaptor<[...]>,[...]>
template <typename alphabet_t>
std::span<alphabet_t> get_database_segment(std::vector<std::vector<alphabet_t>> const & databases,
                                           stellar::StellarOptions const & options,
                                           bool const reverse = false)
{
    auto database = std::span(databases[options.binSequences[0]]);

    if (database.size() < options.segmentEnd)
        throw std::runtime_error{"Segment end out of range"};

    if (options.segmentEnd <= options.segmentBegin)
        throw std::runtime_error{"Incorrect segment definition"};

    if (options.segmentEnd < options.minLength + options.segmentBegin)
        throw std::runtime_error{"Segment shorter than minimum match length"};

    if (reverse)
    {
        return database.subspan(database.size() - options.segmentEnd /* offset */, 
                                options.segmentEnd - options.segmentBegin /* count */);
    }

    return database.subspan(options.segmentBegin /* offset */, options.segmentEnd - options.segmentBegin /* count */);
}

} // namespace dream_stellar
