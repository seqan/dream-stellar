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

#include <dream_stellar/stellar_database_segment.hpp>

namespace dream_stellar
{

template <typename TAlphabet, typename TId = seqan2::CharString>
struct DatabaseIDMap
{
    size_t recordID(StellarDatabaseSegment<TAlphabet> const & databaseSegment) const
    {
        return recordID(databaseSegment.underlyingDatabase());
    }

    size_t recordID(seqan2::String<TAlphabet> const & database) const
    {
        seqan2::String<TAlphabet> const * begin = &databases[0];
        seqan2::String<TAlphabet> const * current = std::addressof(database);
        return current - begin;
    }

    TId const & databaseID(size_t const recordID) const
    {
        return databaseIDs[recordID];
    }

    TId const & databaseID(seqan2::String<TAlphabet> const & database) const
    {
        return databaseIDs[recordID(database)];
    }

    seqan2::StringSet<seqan2::String<TAlphabet> > const & databases;
    seqan2::StringSet<TId> const & databaseIDs;
};

} // namespace dream_stellar
