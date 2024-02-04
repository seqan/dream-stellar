#pragma once

#include <utilities/threshold/shared.hpp>
#include <utilities/threshold/param_set.hpp>

namespace valik
{

/**
 * @brief The user requests filtering by setting the following parameters.
 * 
 * @param e Number of errors.
 * @param l Minimum length of local match.
 * @param s Reference size in bases.
 * @param b Number of reference segments.
*/
struct filtering_request
{
    uint8_t e;
    size_t l;
    uint64_t const s;
    size_t const b;

    filtering_request(uint8_t const errors, size_t const min_len,  
                      uint64_t const ref_size, 
                      size_t const bins) : e(errors), l(min_len), s(ref_size), b(bins)
    {
        auto space = param_space();
        //!TODO: error handling
        if (errors > space.max_errors)
            std::cout << "Error: error count out of range\n";
        
        if (min_len > space.max_len)
            std::cout << "Error: min len out of range\n";
    }

    /**
     * @brief Total number of error configurations.
    */
    uint64_t total_conf_count() const
    {
        return combinations<size_t, uint64_t>(e, l);
    }

    /**
     * @brief Probability of a k-mer appearing spuriously in a bin.
    */
    double kmer_spurious_match_prob(uint8_t const kmer_size) const
    {
        return std::min(1.0f, expected_kmer_occurrences(std::round(s / (float) b), kmer_size));
    }

    /**
     * @brief The probability of at least threshold k-mers matching spuriously between a query pattern and a reference bin.
    */
    double pattern_spurious_match_prob(param_set const & params) const
    {
        double fpr{1};
        double p = kmer_spurious_match_prob(params.k);
        /*
        For parameters 
        
        s reference size
        b number of bins
        k kmer size
        l min match length
        t threshold 

        find the probability of t or more k-mers matching spuriously between a pattern of length l and a reference bin.   
        
        The probability of a pattern exceeding the threshold by chance is equal to 1 - P(0 k-mers match) - 
                                                                                       P(1 k-mer matches) - 
                                                                                       ... - 
                                                                                       P(t - 1 k-mers match).

        Given p which is the probability of a single k-mer appearing spuriously in the reference bin and n = (l - k + 1) k-mers per pattern 
        the probability of 0 k-mers matching spuriously is P(0 k-mers match) = (1 - p)^n 
        and
        the probability of 1 k-mer out of n matching is P(1 k-mer matches) = (n take 1) * p^1 * (1 - p)^(n - 1).
        */

        size_t kmers_per_pattern = l - params.k + 1;
        for (uint8_t matching_kmer_count{0}; matching_kmer_count < params.t; matching_kmer_count++)
        {
            fpr -= combinations<uint8_t, uint64_t>(matching_kmer_count, kmers_per_pattern) * 
                                                  pow(p, matching_kmer_count) * 
                                                  pow(1 - p, kmers_per_pattern - matching_kmer_count);
        }

        return std::max(0.0, fpr);
    }

    /**
     * @brief An approximation of the probability of a query segment having a spurious match in a reference bin. 
    */
    double fpr(param_set const & params, uint64_t const & query_seg_len, uint64_t const & overlap) const
    {
        double pattern_p = pattern_spurious_match_prob(params);
        /*
        uint64_t independent_patterns_per_segment = query_seg_len / (double) l;
        double independent_patterns_p = std::min(1.0, pattern_p * independent_patterns_per_segment);
        std::cout << "independent_patterns_p\t" << independent_patterns_p << '\n';
        */
        uint64_t total_patterns_per_segment = std::round((query_seg_len - l + 1) / (double) (l - overlap));
        double total_patterns_p = std::min(1.0, pattern_p * total_patterns_per_segment);
        std::cout << "total_patterns_p\t" << total_patterns_p << '\n';
        return total_patterns_p;
    }

    /**
     * @brief The maximum length of a query segment that does not appear spuriously in reference bins. 
    */
    uint64_t max_segment_len(param_set const & params) const
    {
        double pattern_p = pattern_spurious_match_prob(params);
        size_t max_independent_patterns_per_segment = std::round(1.0f / pattern_p) - 1;
        return l * max_independent_patterns_per_segment;
    }
};

}   // namespace valik
