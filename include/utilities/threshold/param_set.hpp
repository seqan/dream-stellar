#pragma once

#include <cstdint>

#include <utilities/threshold/basics.hpp>

#include <seqan3/search/kmer_index/shape.hpp>

#include <cereal/archives/binary.hpp> 

namespace valik
{

/**
 * @brief A point in the parameter tuning search space.
 * 
 * @param k K-mer size.
 * @param kmer_weight Less than k-mer size for gapped k-mers.
 * @param t Threshold for minimum number of shared k-mers.
*/
struct param_set
{
    uint8_t k;
    uint8_t kmer_weight;
    uint16_t t;

    param_set() noexcept = default;
    param_set(param_set const &) noexcept = default;
    param_set & operator=(param_set const &) noexcept = default;
    param_set & operator=(param_set &&) noexcept = default;
    ~param_set() noexcept = default;

    param_set(seqan3::shape const shape, uint16_t const thresh, param_space const & space) : k(shape.size()), kmer_weight(shape.count()), t(thresh)
    {
        if ((kmer_weight < std::get<0>(space.kmer_range)) | (kmer_weight > std::get<1>(space.kmer_range)))
        {
            throw std::runtime_error{"k=" + std::to_string(kmer_weight) + " out of range [" + 
                                                std::to_string(std::get<0>(space.kmer_range)) + ", " + 
                                                std::to_string(std::get<1>(space.kmer_range)) + "]"}; 
        }
    
        if (t > space.max_thresh)
        {
            throw std::runtime_error{"t=" + std::to_string(t) + " out of range [0, " + std::to_string(space.max_thresh) + "]"};
        } 
    }

    param_set(uint8_t const kmer_size, uint16_t const thresh, param_space const & space) : 
        param_set(seqan3::shape{seqan3::ungapped{kmer_size}}, thresh, space) { }

    param_set(seqan3::shape const shape, uint16_t const thresh) : k(shape.size()), kmer_weight(shape.count()), t(thresh) {}

    param_set(uint8_t const kmer_size, uint16_t const thresh) : 
        param_set(seqan3::shape{seqan3::ungapped{kmer_size}}, thresh) {}

    template <class Archive>
    void serialize(Archive & archive)
    {
        archive(k, kmer_weight, t);
    }
};

}   // namespace valik
