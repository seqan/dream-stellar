#pragma once

#include <dream_stellar/diagnostics/print.hpp>

namespace dream_stellar
{

///////////////////////////////////////////////////////////////////////////////
// Writes user specified parameters from options object to outStr
template <typename TStream>
void _writeSpecifiedParams(StellarOptions const & options, TStream & outStr)
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
void _writeCalculatedParams(StellarOptions & options, TStream & outStr)
{
//IOREV _notio_
    StellarStatistics statistics{options};

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
void _writeFileNames(StellarOptions const & options, TStream & outStr)
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
template <typename TStringSet, typename TSize, typename TStream>
void _writeMoreCalculatedParams(StellarOptions const & options,
                                TSize const & refLen,
                                TStringSet const & queries,
                                TStream & outStr)
{
//IOREV _notio_
    if (options.qgramAbundanceCut != 1)
    {
        outStr << "Calculated parameters:" << std::endl;
    }

    TSize queryLength = length(concat(queries));
    if (options.qgramAbundanceCut != 1)
    {
        outStr << "  q-gram expected abundance : ";
        outStr << queryLength / (double)((long)1 << (options.qGram << 1)) << std::endl;
        outStr << "  q-gram abundance threshold: ";
        outStr << _max(100, (int)(queryLength * options.qgramAbundanceCut)) << std::endl;
        outStr << std::endl;
    }

    // Computation of maximal E-value for this search

    TSize maxLengthQueries = 0;

    typename Iterator<TStringSet const>::Type queriesIt = begin(queries);
    typename Iterator<TStringSet const>::Type queriesEnd = end(queries);
    while (queriesIt != queriesEnd)
    {
        if (length(*queriesIt) > maxLengthQueries)
        {
            maxLengthQueries = length(*queriesIt);
        }
        ++queriesIt;
    }

    TSize errors = static_cast<TSize>(options.minLength * options.epsilon);
    TSize minScore = options.minLength - (blast_stat::match + blast_stat::mismatch) * errors; // #matches - 2*#errors // #matches = minLenght - errors,

    outStr << "All matches resulting from your search have an E-value of: " << std::endl;
    std::cerr << "refLen\t" << refLen << '\n';
    std::cerr << "maxLengthQueries\t" << maxLengthQueries << '\n';
    std::cerr << "minScore\t" << minScore << '\n';
    
    outStr << "        " << _computeEValueFromScore(refLen, maxLengthQueries, minScore) << " or smaller";
    outStr << "  (match score = " << std::to_string(blast_stat::match) << ", error penalty = -";
    outStr << std::to_string(blast_stat::mismatch) << ")" << std::endl;

    outStr << std::endl;
}

template <typename TStream>
void _printStellarKernelStatistics(StellarComputeStatistics const & statistics, TStream & outStr)
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
    StellarComputeStatistics const & statistics,
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
        StellarComputeStatisticsCollection const & computeStatistics,
        TStream & outStr)
{
    std::cerr << std::endl; // swift filter output is on same line
    for (size_t i = 0; i < length(databaseIDs); ++i)
    {
        CharString const & databaseID = databaseIDs[i];
        StellarComputeStatistics const & statistics = computeStatistics[i];
        _printDatabaseIdAndStellarKernelStatistics(verbose, databaseStrand, databaseID, statistics, outStr);
    }
}

template <typename TStream>
void _writeOutputStatistics(StellarOutputStatistics const & statistics,
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
