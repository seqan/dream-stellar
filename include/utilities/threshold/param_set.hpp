#pragma once

#include <utilities/threshold/basics.hpp>

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
        /*
        if ((kmer_size < std::get<0>(space.kmer_range)) | (kmer_size > std::get<1>(space.kmer_range)))
        {
            throw std::runtime_error{"k=" + std::to_string(kmer_size) + " out of range [" + 
                                                   std::to_string(std::get<0>(space.kmer_range)) + ", " + 
                                                   std::to_string(std::get<1>(space.kmer_range)) + "]"}; 
        }

        if (thresh > space.max_thresh)
        {
            throw std::runtime_error{"threshold=" + std::to_string(thresh) + " out of range [0, " + 
                                                           std::to_string(space.max_thresh) + "]"};
        }
        */
    }
};

}   // namespace valik
