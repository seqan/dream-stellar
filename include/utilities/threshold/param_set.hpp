#pragma once

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
    size_t k;
    size_t t;

    param_set(size_t const kmer_size, size_t const thresh, param_space const & space)
    {
        std::cout << "Considering k=" << kmer_size << " and t=" << thresh << '\n';
        if (kmer_size < std::get<0>(space.kmer_range) | kmer_size > std::get<1>(space.kmer_range))
            std::cout << "Error: k out of range\n";
        else
            k = kmer_size;
        
        if (thresh > space.max_thresh)
            std::cout << "Error: thresh out of range\n";
        else 
            t = thresh;
    }
};

}   // namespace valik
