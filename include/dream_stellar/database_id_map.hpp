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

template <typename alphabet_t, typename id_t = std::string>
struct DatabaseIDMap
{
    size_t recordID(StellarDatabaseSegment<alphabet_t> const & databaseSegment) const
    {
        return recordID(databaseSegment.underlyingDatabase());
    }

    size_t recordID(std::vector<alphabet_t> const & database) const
    {
        std::vector<alphabet_t> const * begin = &databases[0];
        std::vector<alphabet_t> const * current = std::addressof(database);
        return current - begin;
    }

    id_t const & databaseID(size_t const recordID) const
    {
        return databaseIDs[recordID];
    }

    id_t const & databaseID(std::vector<alphabet_t> const & database) const
    {
        return databaseIDs[recordID(database)];
    }

    std::vector<std::vector<alphabet_t> > const & databases;
    std::vector<id_t> const & databaseIDs;
};

} // namespace dream_stellar
