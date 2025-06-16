#pragma once

#include <cstdint>
#include <charconv>

#include <utilities/threshold/kmer.hpp>
#include <utilities/threshold/basics.hpp>

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
    utilities::kmer kmer;
    uint16_t t;

    param_set() noexcept = default;
    param_set(param_set const &) noexcept = default;
    param_set & operator=(param_set const &) noexcept = default;
    param_set & operator=(param_set &&) noexcept = default;
    ~param_set() noexcept = default;

    param_set(utilities::kmer const valik_kmer, uint16_t const thresh, param_space const & space) : kmer(valik_kmer), t(thresh)
    {
        if ((kmer.weight() < std::get<0>(space.kmer_range)) | (kmer.weight() > std::get<1>(space.kmer_range)))
        {
            throw std::runtime_error{"k=" + std::to_string(kmer.weight()) + " out of range [" + 
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

    param_set(seqan3::shape const kmer_shape, uint16_t const thresh) : kmer(kmer_shape), t(thresh) {}

    param_set(uint8_t const kmer_size, uint16_t const thresh) : 
        param_set(seqan3::shape{seqan3::ungapped{kmer_size}}, thresh) {}

    param_set(utilities::kmer const & k, uint16_t const thresh) : kmer{k}, t{thresh} {}


    param_set get_equivalent_gapped() const
    {
        if (kmer.is_gapped())
            return *this;
        else
        {
            assert(kmer.size() == kmer.weight());
            
            std::string gapped_str = BEST_WEIGHT12;
            if (kmer.size() > BEST_WEIGHT)
            {
                if ((kmer.size() - BEST_WEIGHT) % 2u == 0)
                {
                    gapped_str = std::string(std::floor((kmer.size() - BEST_WEIGHT) / 2.0), '1') + 
                                 BEST_WEIGHT12 + 
                                 std::string(std::ceil((kmer.size() - BEST_WEIGHT) / 2.0), '1');            
                }
                else
                {
                    gapped_str = std::string(std::floor((kmer.size() - BEST_WEIGHT) / 2.0), '1') + 
                                 BEST_WEIGHT12.substr(0, BEST_WEIGHT12.size() / 2) +
                                 std::string((kmer.size() - BEST_WEIGHT) % 2u, '1') + 
                                 BEST_WEIGHT12.substr(BEST_WEIGHT12.size() / 2) + 
                                 std::string(std::floor((kmer.size() - BEST_WEIGHT) / 2.0), '1');                                
                }
            }
            
            uint64_t bin_shape{};
            std::from_chars(gapped_str.data(), gapped_str.data() + gapped_str.size(), bin_shape, 2);
            auto best_shape = seqan3::shape(seqan3::bin_literal{bin_shape});
            assert(best_shape.count() == kmer.size());
            return param_set{best_shape, t};
        }
    }

    template<class Archive>
    void save(Archive & archive) const
    {
        archive(kmer.to_string(), t); 
    }

    template<class Archive>
    void load(Archive & archive)
    {
        std::string shape_str;
        archive(shape_str, t);
        uint64_t bin_shape{};
        std::from_chars(shape_str.data(), shape_str.data() + shape_str.size(), bin_shape, 2);
        kmer = utilities::kmer{seqan3::shape(seqan3::bin_literal{bin_shape})};
    }
};

}   // namespace valik
