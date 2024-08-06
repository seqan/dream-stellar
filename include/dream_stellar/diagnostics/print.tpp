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

#include <dream_stellar/diagnostics/print.hpp>

namespace dream_stellar
{

using namespace seqan2;

///////////////////////////////////////////////////////////////////////////////
// Writes user specified parameters from options object to outStr
template <typename TStream>
void _writeSpecifiedParams(stellar::StellarOptions const & options, TStream & outStr)
{
//IOREV _notio_
    // Output user specified parameters
    outStr << "User specified parameters:" << std::endl;
    outStr << "  minimal match length             : " << options.minLength << std::endl;
    outStr << "  maximal error rate (epsilon)     : " << options.epsilon << std::endl;
    outStr << "  maximal x-drop                   : " << options.xDrop << std::endl;
    if (options.qGram != std::numeric_limits<size_t>::max())
        outStr << "  k-mer (q-gram) length            : " << options.qGram << std::endl;
    outStr << "  search forward strand            : " << ((options.forward) ? "yes" : "no") << std::endl;
    outStr << "  search reverse complement        : " << ((options.reverse) ? "yes" : "no") << std::endl;
    outStr << std::endl;

    outStr << "  verification strategy            : " << to_string(options.verificationMethod) << std::endl;
    if (options.disableThresh != std::numeric_limits<size_t>::max())
    {
        outStr << "  disable queries with more than   : " << options.disableThresh << " matches" << std::endl;
    }
    outStr << "  maximal number of matches        : " << options.numMatches << std::endl;
    outStr << "  duplicate removal every          : " << options.compactThresh << std::endl;
    if (options.maxRepeatPeriod != 1 || options.minRepeatLength != 1000)
    {
        outStr << "  max low complexity repeat period : " << options.maxRepeatPeriod << std::endl;
        outStr << "  min low complexity repeat length : " << options.minRepeatLength << std::endl;
    }
    if (options.qgramAbundanceCut != 1)
    {
        outStr << "  q-gram abundance cut ratio       : " << options.qgramAbundanceCut << std::endl;
    }

    outStr << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// Calculates parameters from parameters in options object and writes them to outStr
// Sets options.qGram if not set by user input
template <typename TStream>
void _writeCalculatedParams(stellar::StellarOptions & options, TStream & outStr)
{
//IOREV _notio_
    stellar::StellarStatistics statistics{options};

    outStr << "Calculated parameters:" << std::endl;
    if (statistics.kMerComputed)
    {
        options.qGram = (unsigned)statistics.kMerLength;
        outStr << "  k-mer length : " << statistics.kMerLength << std::endl;
    }

    outStr << "  s^min        : " << statistics.smin << std::endl;
    outStr << "  threshold    : " << statistics.threshold << std::endl;
    outStr << "  distance cut : " << statistics.distanceCut << std::endl;
    outStr << "  delta        : " << statistics.delta << std::endl;
    outStr << "  overlap      : " << statistics.overlap << std::endl;
    outStr << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// Writes file name from options object to outStr
template <typename TStream>
void _writeFileNames(stellar::StellarOptions const & options, TStream & outStr)
{
//IOREV _notio_
    outStr << "I/O options:" << std::endl;
    outStr << "  database file   : " << options.databaseFile << std::endl;
    outStr << "  query file      : " << options.queryFile << std::endl;
    outStr << "  alphabet        : " << options.alphabet << std::endl;
    outStr << "  output file     : " << options.outputFile << std::endl;
    outStr << "  output format   : " << options.outputFormat << std::endl;
    if (options.disableThresh != std::numeric_limits<size_t>::max())
    {
        outStr << "  disabled queries: " << options.disabledQueriesFile << std::endl;
    }
    outStr << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// Calculates parameters from parameters in options object and from sequences and writes them to outStr
template <typename sequence_t, typename TStream>
void _writeMoreCalculatedParams(stellar::StellarOptions const & options,
                                uint64_t const & refLen,
                                std::vector<sequence_t> const & queries,
                                TStream & outStr)
{
    if (options.qgramAbundanceCut != 1)
    {
        outStr << "Calculated parameters:" << std::endl;
    }

    uint64_t queryLength{0};
    for (auto & query : queries)
        queryLength += query.size();

    if (options.qgramAbundanceCut != 1)
    {
        outStr << "  q-gram expected abundance : ";
        outStr << queryLength / (double)((long)1 << (options.qGram << 1)) << std::endl;
        outStr << "  q-gram abundance threshold: ";
        outStr << _max(100, (int)(queryLength * options.qgramAbundanceCut)) << std::endl;
        outStr << std::endl;
    }
}

template <typename TStream>
void _printStellarKernelStatistics(stellar::StellarComputeStatistics const & statistics, TStream & outStr)
{
    if (statistics.numSwiftHits == 0)
        return;

    outStr << std::endl << "    # SWIFT hits      : " << statistics.numSwiftHits;
    outStr << std::endl << "    Longest hit       : " << statistics.maxLength;
    outStr << std::endl << "    Avg hit length    : " << statistics.totalLength/statistics.numSwiftHits;
}

template <typename TStream>
void _printDatabaseIdAndStellarKernelStatistics(
    bool const verbose,
    bool const databaseStrand,
    CharString const & databaseID,
    stellar::StellarComputeStatistics const & statistics,
    TStream & outStr)
{
    outStr << "  " << databaseID;
    if (!databaseStrand)
        outStr << ", complement";
    outStr << std::flush;

    if (verbose)
    {
        _printStellarKernelStatistics(statistics, outStr);
    }
    outStr << std::endl;
}

template <typename TStream>
void _printStellarStatistics(
        bool const verbose,
        bool const databaseStrand,
        StringSet<CharString> const & databaseIDs,
        stellar::StellarComputeStatisticsCollection const & computeStatistics,
        TStream & outStr)
{
    std::cerr << std::endl; // swift filter output is on same line
    for (size_t i = 0; i < length(databaseIDs); ++i)
    {
        CharString const & databaseID = databaseIDs[i];
        stellar::StellarComputeStatistics const & statistics = computeStatistics[i];
        _printDatabaseIdAndStellarKernelStatistics(verbose, databaseStrand, databaseID, statistics, outStr);
    }
}

template <typename TStream>
void _writeOutputStatistics(stellar::StellarOutputStatistics const & statistics,
                            bool const verbose,
                            bool const writeDisabledQueriesFile,
                            TStream & outStr)
{
    outStr << "# Eps-matches     : " << statistics.numMatches << std::endl;
    if (verbose) {
        if (statistics.numMatches > 0) {
            outStr << "Longest eps-match : " << statistics.maxLength << std::endl;
            outStr << "Avg match length  : " << statistics.totalLength / statistics.numMatches << std::endl;
        }
        if (writeDisabledQueriesFile)
            outStr << "# Disabled queries: " << statistics.numDisabled << std::endl;
    }
}

} // namespace dream_stellar
