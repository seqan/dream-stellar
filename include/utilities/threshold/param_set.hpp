#pragma once

#include <utilities/threshold/shared.hpp>

namespace valik
{

/**
 * @brief A point in the parameter tuning search space.
 * 
 * @param k K-mer size.
 * @param t Threshold for minimum number of shared k-mers.
*/
struct param_set
{
    uint8_t k;
    uint8_t t;

    param_set(uint8_t const kmer_size, uint8_t const thresh, param_space const & space) : k(kmer_size), t(thresh)
    {
        if ((kmer_size < std::get<0>(space.kmer_range)) | (kmer_size > std::get<1>(space.kmer_range)))
            std::cout << "Error: k out of range\n";
        
        if (thresh > space.max_thresh)
            std::cout << "Error: thresh out of range\n";
    }
};

}   // namespace valik
