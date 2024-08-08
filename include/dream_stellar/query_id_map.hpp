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

#include <stellar/stellar_index.hpp>
#include <stellar/stellar_query_segment.hpp>
#include <stellar/stellar_types.hpp>

namespace dream_stellar
{

template <typename TAlphabet, typename TId = std::string>
struct QueryIDMap
{
    size_t recordID(std::vector<TAlphabet> const & query) const
    {
        std::vector<TAlphabet> const * begin = &queries[0];
        std::vector<TAlphabet> const * current = std::addressof(query);
        return current - begin;
    }

    std::vector<std::vector<TAlphabet> > const & queries;
};

} // namespace dream_stellar
