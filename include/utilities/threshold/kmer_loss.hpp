#pragma once

#include <utilities/threshold/param_set.hpp>
#include <utilities/threshold/search_pattern.hpp>

namespace valik
{

/**
 * @brief For a kmer size k consider how the FNR changes for various values of the parameters t, e and l. 
 *   
 * @param k Chosen k-mer size.
 * @param fn_conf_counts Number of configurations of e errors that do not retain at least t shared kmers after mutation.
*/
struct kmer_loss
{
    using row_t = std::vector<uint64_t>;
    using table_t = std::vector<row_t>;
    using mat_t = std::vector<table_t>;
    
    const uint8_t k;
    const mat_t fn_conf_counts;  // false negative configuration counts

    /**
     * @brief For a maximum error count find the number of error configurations 
     *        that do not retain at least the threshold number of k-mers after mutation.
    */
    mat_t count_err_conf_below_thresh(param_space const & space)
    {
        mat_t matrix;
        for (uint8_t t = 1; t <= space.max_thresh; t++)
        {
            table_t table;
            for (uint8_t e = 0; e <= space.max_errors; e++)
            {
                row_t row;
                for(size_t l = 0; l <= space.max_len; l++)
                {       
                    int shared_base_count = l - e;
                    if ((int) (k + t) - 1 > shared_base_count) // all error distributions destroy enough k-mers
                        row.push_back(combinations(e, l));
                    else if (e == 0)    // this has to be after the first condition; not everything in first row should be 0
                        row.push_back(0);
                    else
                    {                        
                        row.push_back(row.back() + table.back()[l - 1]);
                        row.back() -= table.back()[l - k - 1];

                        for (uint8_t i = 1; i < t; i++)
                        {
                            row.back() -= matrix[matrix.size() - i][e - 1][l - k - i - 1];
                            row.back() += matrix[matrix.size() - i][e - 1][l - k - i];
                        }
                    }
                }
                table.push_back(row);
            }
            matrix.push_back(table);
        }
        return matrix;
    }

    kmer_loss(uint8_t const kmer_size, param_space const & space) : 
                    k(kmer_size), 
                    fn_conf_counts(count_err_conf_below_thresh(space)) { }

    kmer_loss(uint8_t const kmer_size, mat_t const & matrix) : k(kmer_size), fn_conf_counts(matrix) { }

    kmer_loss(std::string const & kmer_attr_str) : 
    {
        deserialize_kmer_loss(kmer_attr_str);
    }

    /**
     * @brief False negative rate for a parameter set.
    */
    double fnr_for_param_set(search_pattern const & pattern, param_set const & params) const
    {        
        if (kmer_lemma_threshold(pattern.l, params.k, pattern.e) >= params.t)
            return 0.0;
        if (params.t > fn_conf_counts.size())
            throw std::runtime_error("Calculated configuration count table for t=[1, " + std::to_string(fn_conf_counts.size()) + "]. " 
                                     "Can't find FNR for t=" + std::to_string(params.t));
        return fn_conf_counts[params.t - 1][pattern.e][pattern.l] / (double) pattern.total_conf_count();
    }

    /** //!TODO: use cereal
     * @brief Stream out flattened 3D matrix of false negative configuration counts.
    */
    template <typename str_t>
    void serialize(str_t & outstr)
    {
        outstr << "k=" << std::to_string(k) << '\n'; 
        size_t t = 1;
        for (auto threshold_table : fn_conf_counts)
        {   
            outstr << "t=" << t << '\n';
            for (auto error_row : threshold_table)
            {
                for (auto cell : error_row)
                    outstr << cell << '\t';
                outstr << '\n';
            }
            t++;
        }
    }

    private:
        //!TODO: use cereal
        /**
         * @brief Deserialize kmer_loss for a single k-mer size.
        */
        kmer_loss deserialize_kmer_loss(std::string const & kmer_attr_str)
        {
            std::istringstream matrix_str(kmer_attr_str);
            std::string line;
            std::getline(matrix_str, line);
            k{0};
            try
            {
                k = std::stoi(line.substr(line.find("k=") + 2));
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << "\nCan't convert " << line.substr(line.find("k=") + 2)  << "to k-mer size\n";
            }

            std::vector<std::vector<uint64_t>> table;
            for (; std::getline(matrix_str, line); )
            {
                bool is_first_thresh_row{false};
                try
                {
                    is_first_thresh_row = (stoi(line.substr(line.find("t=") + 2)) == 1);
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << "\nCan't convert " << line.substr(line.find("t=") + 2) << " to threshold\n";
                }

                std::istringstream row_str(line);
                if (line.find("t=") == std::string::npos)
                {
                    std::string cell;
                    std::vector<uint64_t> row;
                    for (; std::getline(row_str, cell, '\t'); )
                    {
                        try
                        {
                            row.push_back(std::stoull(cell));
                        }
                        catch(const std::exception& e)
                        {
                            std::cerr << e.what() << "\nCan't convert cell value\t" << cell << '\n';
                        }
                    }
                    table.push_back(row);
                }
                else if (is_first_thresh_row)
                {
                    continue;
                }
                else
                {
                    fn_conf_counts.push_back(table);
                    table.clear();
                }
            }   

            fn_conf_counts.push_back(table);
        }
};

}   // namespace valik
