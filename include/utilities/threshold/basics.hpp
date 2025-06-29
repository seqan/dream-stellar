#pragma once

#include <algorithm>
#include <iostream>
#include <fstream>
#include <cmath>
#include <numeric>
#include <vector>
#include <utility>
#include <filesystem>
#include <map>

#include <cereal/archives/binary.hpp> 
#include <cereal/types/tuple.hpp>

#include <utilities/threshold/kmer.hpp>

// Workaround, seqan3 IBF includes sdsl, which defines ALPHABET_SIZE.
#ifdef ALPHABET_SIZE
#undef ALPHABET_SIZE
#endif

namespace valik
{

constexpr double FPR_UPPER{0.045};
constexpr double EXACT_FNR_UPPER{0.01};
constexpr double MIN_FNR_UPPER{0.1};

constexpr uint8_t THRESH_LOWER{2};
constexpr size_t PATTERNS_PER_SEGMENT{1000};

enum class search_kind {LEMMA, HEURISTIC, GAPPED, STELLAR};

// symmetrical seed where adjacent k-mers share only 5 positions
static const std::string BEST_WEIGHT12{"111010101101010111"};
constexpr uint8_t BEST_WEIGHT{12};

constexpr uint8_t ALPHABET_SIZE{4}; // DNA4
constexpr uint8_t QUERY_EVERY = 2; // query every 2nd pattern by default

/**
 *  @brief Assuming k-mers are distributed uniformly randomly, what is the expected count of a k-mer in a bin.
 * 
 * @param bin_size Size of reference segment in bases.
 * @param kmer_size K-mer size.
 * 
*/
template <typename var_t>
double expected_kmer_occurrences(var_t const bin_size,
                                utilities::kmer const & kmer, 
                                double const information_content)
{
    var_t total_kmer_count = bin_size - kmer.size() + 1;
    return (double) 2u*(total_kmer_count) / ((double) pow(ALPHABET_SIZE, kmer.weight()) * information_content);
}

/**
 * @brief The false positive probability of a query segment that contains partially overlapping patterns.
*/
inline double segment_fpr(double const pattern_p, size_t const patterns_per_segment)
{
    double none_match_p = pow(1 - pattern_p, patterns_per_segment);
    return std::min(1 - none_match_p, 1.0);
}

/**
* @brief The maximum length of a query segment that does not appear spuriously in reference bins. 
*/
inline uint64_t max_segment_len(double const /*pattern_p*/, size_t const pattern_size, uint8_t query_every)
{
    //!TODO: this const is the *minimum* number of patterns per segment
    // higher values are possible if pattern_p is small    
    return pattern_size + query_every * (PATTERNS_PER_SEGMENT - 1);
}


/**
 * @brief Definition of the search space for the parameter tuning algorithm.
 * 
 * @param max_errors Maximum number of errors.
 * @param max_thresh Maximum thershold for the number of k-mers that are shared after introducing errors.
 * @param max_len The highest minimum local match length to consider.
 * @param kmer_range The range of k-mer sizes.
*/
struct param_space
{
    constexpr static uint8_t max_errors{15};    
    uint16_t max_thresh{25};
    constexpr static size_t max_len{150};
    constexpr static std::pair<uint8_t, uint8_t> kmer_range{7, 23};

    param_space() noexcept = default;
    param_space(param_space const &) noexcept = default;
    param_space & operator=(param_space const &) noexcept = default;
    param_space & operator=(param_space &&) noexcept = default;
    ~param_space() noexcept = default;

    param_space(uint16_t thresh) : max_thresh(thresh) {}

    uint8_t min_k() const
    {
        return std::get<0>(kmer_range);
    }

    uint8_t max_k() const
    {
        return std::get<1>(kmer_range);
    }

    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(max_thresh);
    }
};

/**
 * @brief Number of combinations of n take k.
 * 
 * Same as the number of different error configurations if n=sequence length and k=error_count. 
*/
inline uint64_t combinations(size_t const k, size_t const n)
{
    if (n >= k)
    {
        std::vector<size_t> divisors(k);
        std::iota(divisors.begin(), divisors.end(), 1); // fill vector with 1, 2, ..., k
        std::vector<bool> was_divided(k);

        uint64_t combinations{1};
        for (size_t i = n - k + 1; i <= n; i++)
        {
            // avoid overflowing 64bits
            if (combinations >= (std::numeric_limits<uint64_t>::max() / n))
            {
                for (size_t i{0}; i < divisors.size(); i++)
                {
                    if (!was_divided[i])
                    {
                        if (combinations % divisors[i] == 0)
                        {
                            combinations = combinations / divisors[i];
                            was_divided[i] = true;
                        }
                    }
                }
            }
            combinations *= i;
        }
        
        if (std::find(was_divided.begin(), was_divided.end(), false) != was_divided.end())
        {
            for (size_t i{0}; i < divisors.size(); i++)
            {
                if (!was_divided[i])
                    combinations = combinations / divisors[i];
            }
        }
        return combinations;   // same as (uint64_t) (factorial(n) / (factorial(n - k) * factorial(k)));
    }
    else
        return 0;
}

}   //namespace valik
