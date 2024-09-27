#pragma once

#include <cstdint>

///////////////////////////////////////////////////////////////////////////////
// Karlin-Altschul values for a scoring scheme with linear gap costs.
// 
// These values were found empirically and are copied from BLAST 2.16
//      BLAST source code https://ftp.ncbi.nlm.nih.gov/blast/executables/blast+/LATEST/
//      Values hard coded in ncbi-blast-2.16.0+-src/c++/src/algo/blast/core/blast_stat.c
namespace blast_stat
{
    constexpr uint8_t match = 1;
    constexpr uint8_t mismatch = 2;
    constexpr double lambda = 1.28;
    constexpr double K = 0.46;
    constexpr double alpha = 1.5; 
    constexpr double beta = -2;

} // namespace blast_stat
