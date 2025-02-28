#pragma once

#include <cstdint>
#include <charconv>
#include <string>

#include <seqan3/search/kmer_index/shape.hpp>
#include <seqan3/core/debug_stream.hpp>

#include <cereal/archives/binary.hpp> 
#include <cereal/types/string.hpp>

namespace utilities
{

/**
 * @brief A sequence submer.
 * 
 * @param k K-mer size.
 * @param kmer_weight Less than k-mer size for gapped k-mers.
 * @param t Threshold for minimum number of shared k-mers.
*/
struct kmer
{
    seqan3::shape shape;

    kmer() noexcept = default;
    kmer(kmer const &) noexcept = default;
    kmer & operator=(kmer const &) noexcept = default;
    kmer & operator=(kmer &&) noexcept = default;
    ~kmer() noexcept = default;

    kmer(seqan3::shape const kmer_shape) : shape(kmer_shape) {}

    kmer(uint8_t const kmer_size) : 
        kmer(seqan3::shape{seqan3::ungapped{kmer_size}}) {}

    bool is_gapped() const
    {
        return shape.count() < shape.size();
    }

    uint8_t longest_ungapped() const
    {
        if (is_gapped())
        {
            uint8_t longest_ungapped{0};
            uint8_t curr_ungapped{0};
            for (auto c : shape.to_string())
            {
                if (c == '1')
                    curr_ungapped++;
                else
                {
                    if (curr_ungapped > longest_ungapped)
                        longest_ungapped = curr_ungapped;
                    curr_ungapped = 0;
                }
            }
            if (curr_ungapped > longest_ungapped)
                longest_ungapped = curr_ungapped;
            
            return longest_ungapped;
        }
        else
            return shape.count();
    }

    //!TODO: cout triplets
    uint8_t ungapped_triplet_length() const
    {
        if (is_gapped())
        {
            uint8_t ungapped_triplet_length{0};
            std::vector<size_t> triplet_pos{};

            std::string shape_str = to_string();
            std::string substr{"111"};
            size_t pos = shape_str.find(substr, 0);
            while( pos != std::string::npos )
            {
                triplet_pos.push_back(pos);
                pos = shape_str.find(substr, pos+1);
            }
            
            if (!triplet_pos.empty())
            {
                size_t prev_pos = *triplet_pos.begin();
                for (auto it = triplet_pos.begin(); it < triplet_pos.end(); ++it)
                {
                    if (*it == (prev_pos + 1))
                        ungapped_triplet_length++;
                    else
                        ungapped_triplet_length += 3;
                    prev_pos = *it;
                }
            }

            return ungapped_triplet_length;
        }
        else
            return size();
    }

    uint8_t weight() const
    {
        return shape.count();
    }

    uint8_t size() const
    {
        return shape.size();
    }

    uint8_t effective_size() const
    {
        if (is_gapped())
        {
            // 28 18 20 16
            // double ungapped_frac = weight() / (double) size();
            // return std::round(longest_ungapped() * (1 + ungapped_frac));
            // 
            // 28 17 18 13
            return ungapped_triplet_length();
        }
        else
            return size();
    }

    std::string to_string() const
    {
        return shape.to_string();
    }

    bool operator==(kmer const & other) const
    {
        return (to_string() == other.to_string());
    }

    /**
     * @brief K-mer lemma threshold.
    */
    inline size_t lemma_threshold(size_t const l, uint8_t const e) const
    {
        uint8_t k = size();
        if (l < k)
            return 0;
        if ((l - k + 1) <= (size_t) e*k)
            return 0;

        return l - k + 1 - e * k;
    }

    /**
     * @brief Gapped k-mer threshold.
    */
    inline size_t gapped_threshold(size_t const l, uint8_t const e) const
    {
        uint8_t k = size();
        if (l < k)
            return 0;
        if ((l - k + 1) <= (size_t) e*effective_size())
            return 0;

        return l - k + 1 - e * effective_size();
    }

    template<class Archive>
    void save(Archive & archive) const
    {
        archive(shape.to_string()); 
    }

    template<class Archive>
    void load(Archive & archive)
    {
        std::string shape_str;
        archive(shape_str);
        uint64_t bin_shape{};
        std::from_chars(shape_str.data(), shape_str.data() + shape_str.size(), bin_shape, 2);
        shape = seqan3::shape(seqan3::bin_literal{bin_shape});
    }
};

}   // namespace utilities
