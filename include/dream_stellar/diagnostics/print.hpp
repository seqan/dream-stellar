
#pragma once

#include <dream_stellar/stellar_types.hpp>
#include <dream_stellar/stellar_output.hpp>

namespace dream_stellar
{

///////////////////////////////////////////////////////////////////////////////
// Calculates parameters from parameters in options object and writes them to outStr
// Sets options.qGram if not set by user input
template <typename TStream>
void _writeCalculatedParams(StellarOptions & options, TStream & outStr);

///////////////////////////////////////////////////////////////////////////////
// Writes user specified parameters from options object to outStr
template <typename TStream>
void _writeSpecifiedParams(StellarOptions const & options, TStream & outStr);

///////////////////////////////////////////////////////////////////////////////
// Writes file name from options object to outStr
template <typename TStream>
void _writeFileNames(StellarOptions const & options, TStream & outStr);

///////////////////////////////////////////////////////////////////////////////
// Calculates parameters from parameters in options object and from sequences and writes them to outStr
template <typename TStringSet, typename TSize, typename TStream>
void _writeMoreCalculatedParams(StellarOptions const & options,
                                TSize const & refLen,
                                TStringSet const & queries,
                                TStream & outStr);

void _writeOutputStatistics(StellarOutputStatistics const & statistics, bool const verbose, bool const writeDisabledQueriesFile);

template <typename TStream>
void _printStellarKernelStatistics(StellarComputeStatistics const & statistics, TStream & outStr);

template <typename TStream>
void _printDatabaseIdAndStellarKernelStatistics(
    bool const verbose,
    bool const databaseStrand,
    CharString const & databaseID,
    StellarComputeStatistics const & statistics,
    TStream & outStr);

template <typename TStream>
void _printStellarStatistics(
    bool const verbose,
    bool const databaseStrand,
    StringSet<CharString> const & databaseIDs,
    StellarComputeStatisticsCollection const & computeStatistics,
    TStream & outStr);

template <typename TStream>
void _writeOutputStatistics(StellarOutputStatistics const & statistics,
                            bool const verbose,
                            bool const writeDisabledQueriesFile,
                            TStream & outStr);

} // namespace dream_stellar
