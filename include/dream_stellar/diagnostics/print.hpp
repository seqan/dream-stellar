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

#include <dream_stellar/stellar_types.hpp>
#include <stellar/stellar_output.hpp>

namespace dream_stellar
{

using namespace seqan2;

///////////////////////////////////////////////////////////////////////////////
// Calculates parameters from parameters in options object and writes them to outStr
// Sets options.qGram if not set by user input
template <typename TStream>
void _writeCalculatedParams(stellar::StellarOptions & options, TStream & outStr);

///////////////////////////////////////////////////////////////////////////////
// Writes user specified parameters from options object to outStr
template <typename TStream>
void _writeSpecifiedParams(stellar::StellarOptions const & options, TStream & outStr);

///////////////////////////////////////////////////////////////////////////////
// Writes file name from options object to outStr
template <typename TStream>
void _writeFileNames(stellar::StellarOptions const & options, TStream & outStr);

///////////////////////////////////////////////////////////////////////////////
// Calculates parameters from parameters in options object and from sequences and writes them to outStr
template <typename TStringSet, typename TSize, typename TStream>
void _writeMoreCalculatedParams(stellar::StellarOptions const & options,
                                TSize const & refLen,
                                TStringSet const & queries,
                                TStream & outStr);

void _writeOutputStatistics(stellar::StellarOutputStatistics const & statistics, bool const verbose, bool const writeDisabledQueriesFile);

template <typename TStream>
void _printStellarKernelStatistics(stellar::StellarComputeStatistics const & statistics, TStream & outStr);

template <typename TStream>
void _printDatabaseIdAndStellarKernelStatistics(
    bool const verbose,
    bool const databaseStrand,
    CharString const & databaseID,
    stellar::StellarComputeStatistics const & statistics,
    TStream & outStr);

template <typename TStream>
void _printStellarStatistics(
    bool const verbose,
    bool const databaseStrand,
    StringSet<CharString> const & databaseIDs,
    stellar::StellarComputeStatisticsCollection const & computeStatistics,
    TStream & outStr);

template <typename TStream>
void _writeOutputStatistics(stellar::StellarOutputStatistics const & statistics,
                            bool const verbose,
                            bool const writeDisabledQueriesFile,
                            TStream & outStr);

} // namespace dream_stellar
