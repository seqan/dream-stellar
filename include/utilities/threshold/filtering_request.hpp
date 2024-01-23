#pragma once

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
    size_t e;
    size_t l;
    uint64_t const s;
    size_t const b;

    filtering_request(size_t const errors, size_t const min_len,  
                      uint64_t const ref_size, 
                      size_t const bins) : s(ref_size), b(bins) 
    {
        auto space = parameter_space();
        std::cout << "Find suitable parameters for e=" << errors << " and l=" << min_len << '\n';
        if (errors > space.max_errors)
            std::cout << "Error: error count out of range\n";
        else 
            e = errors;
        
        if (min_len > space.max_len)
            std::cout << "Error: min len out of range\n";
        else
            l = min_len;        
    }

    /**
     * @brief Total number of error configurations.
    */
    uint64_t total_conf_count() const
    {
        return total_err_conf_count(e, l);
    }

    /**
     * @brief Expected number of spuriously matching k-mers in a bin.
    */
    double fpr(size_t const & kmer_size) const
    {
        return expected_kmer_occurrences(std::round(s / (float) b), kmer_size);
    }
};
