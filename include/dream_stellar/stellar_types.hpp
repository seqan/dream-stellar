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

namespace dream_stellar
{

///////////////////////////////////////////////////////////////////////////////
// Container for storing local alignment matches of one query sequence
template<typename TMatch_>
struct QueryMatches {
    typedef typename TMatch_::TSequence::size_type TSize;

    std::vector<TMatch_> matches;
    bool disabled;
    TSize lengthAdjustment;

    QueryMatches() : disabled(false), lengthAdjustment(0)
    {}
 
    inline bool removeOverlapsAndCompactMatches(size_t const disableThresh,
                                                size_t const compactThresh,
                                                size_t const minLength,
                                                size_t const numMatches)
    {
        if (this->disabled)
            return false;

        size_t const matchesCount = (this->matches).size();

        if (matchesCount > disableThresh) {
            this->disabled = true;
            (this->matches).clear();
            return false;
        }

        if (matchesCount <= compactThresh)
            return false;

        //!TODO: reimplement for std::vector
        //maskOverlaps(this->matches, minLength);      // remove overlaps and duplicates
        //compactMatches(this->matches, numMatches);   // keep only the <numMatches> longest matches
        return true;
    }
};

///////////////////////////////////////////////////////////////////////////////
// Container for storing a local alignment match
template<typename TSequence_, typename TId_>
struct StellarMatch {
    static_assert(std::is_const<TSequence_>::value, "Sequence must be const qualified! I.e. StellarMatch<... const, ...>");
    typedef TSequence_                          TSequence;
    typedef TId_                                TId;
    typedef typename TSequence::size_type  TPos;

    /*
    typedef Align<TSequence, ArrayGaps>         TAlign;
    typedef typename Row<TAlign>::Type         TRow;
    */
    static const TId INVALID_ID;

    TId id;         // database ID
    bool orientation;
    TPos begin1;
    TPos end1;
    //TRow row1;

    TPos begin2;
    TPos end2;
    //TRow row2;

    StellarMatch() : id(), orientation(false), begin1(0), end1(0), begin2(0), end2(0)
    {}

    /*
    template <typename TAlign, typename TId>
    StellarMatch(TAlign & _align, TId _id, bool _orientation)
    {
        id = _id;
        orientation = _orientation;
        row1 = row(_align, 0);
        row2 = row(_align, 1);

        begin1 = beginPosition(row1);
        end1 = endPosition(row1);

        begin2 = beginPosition(row2);
        end2 = endPosition(row2);
    }
    */
};

} // namespace dream_stellar
