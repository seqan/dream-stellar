#include <iostream>
#include <cmath>
#include <numbers>
#include <vector>
#include <utility>

template <typename val_t>
val_t stirling_factorial(val_t const n)
{
    return sqrt(2 * std::numbers::pi * n) * pow((n / std::numbers::e), (double) n);
}

template <typename val_t>
val_t exact_factorial(val_t const n)
{
    val_t fact{1};
    for (size_t i = 2; i <= n; i++)
        fact *= i;

    return fact;
}

template <typename val_t>
val_t factorial(val_t const n)
{
    if (n < 25)
        return exact_factorial(n);
    else 
        return stirling_factorial(n);
}

template <typename vec_t>
void print_matrix(vec_t const & matrix)
{
    using par_t = vec_t::value_type::value_type::value_type;
    for (auto table : matrix)
    {
        std::cout << "\t";
        for (par_t l = 0; l < table[0].size(); l++)
        {
            std::cout << l << '\t';
        }
        std::cout << '\n';

        for (par_t e = 0; e < table.size(); e++)
        {
            std::cout << e << '\t';
            for (par_t l = 0; l < table[e].size(); l++)
            {
                auto cell = table[e][l];
                std::cout << cell << '\t';
            }
            std::cout << '\n';
        }
    }
}

/**
* @brief Assuming k-mers are distributed uniformly randomly, what is the expected count of a k-mer in a bin.
*/
template <typename var_t, typename par_t>
float expected_kmer_occurrences(var_t const & bin_size,
                               par_t const & kmer_size)
{
    size_t alphabet_size = 4;
    return (float) (bin_size - kmer_size + 1) / (float) pow(alphabet_size, kmer_size);
}

// Define the search space for the parameter tuning algorithm
struct parameter_space
{
    constexpr static size_t max_errors{3};    
    constexpr static size_t max_thresh{3};
    constexpr static size_t max_len{20};
    constexpr static std::pair<size_t, size_t> kmer_range{9, 15};
};

uint64_t total_err_conf_count(size_t const error_count, size_t const len)
{
    if (len >= error_count)
    {
        uint64_t combinations{1};
        for (size_t i = len - error_count + 1; i <= len; i++)
            combinations *= i;
        combinations = combinations / factorial(error_count);
        return combinations;   // same as (uint64_t) (factorial(len) / (factorial(len - error_count) * factorial(error_count)));
    }
    else
        return (uint64_t) 0;
}

// The user requests filtering by setting the following parameters 
struct filtering_request
{
    size_t e;   // chosen error count
    size_t l;   // chosen length
    uint64_t total_conf_count;  // how many error conf in total
    uint64_t const s;   // reference size
    size_t const b; // number of bins

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
        
        total_conf_count = total_err_conf_count(e, l);
    }
};

// Represents a point in the parameter tuning search space
// for all possible values for kmer length and threshold
struct param_set
{
    size_t k;
    size_t t;

    param_set(size_t const kmer_size, size_t const thresh, parameter_space const & space)
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

// For a reference of certain size and number of bins and a set kmer length
// Consider how the FNR changes for various values of the parameters t, e, l
struct kmer_attributes
{
    using row_t = std::vector<uint64_t>;
    using table_t = std::vector<row_t>;
    using mat_t = std::vector<table_t>;
    
    const size_t k; 
    const double fpr;
    const std::vector<std::vector<std::vector<uint64_t>>> fn_conf_counts;

    /**
     * @brief For a maximum error count find the number of error configurations 
     *        that do not retain at least the threshold number of k-mers after mutation.
     * 
     * @param kmer_size K-mer length.
     * @param threshold Minimum number of shared k-mers for success.
     * @param error_count Number of errors.
     * @param len Length of sequences being compared.
    */
    mat_t count_err_conf_below_thresh()
    {
        auto space = parameter_space();
        mat_t matrix;
        for (size_t t = 1; t <= space.max_thresh; t++)
        {
            table_t table;
            for (size_t e = 0; e <= space.max_errors; e++)
            {
                row_t row;
                for(size_t l = 0; l <= space.max_len; l++)
                {       
                    int shared_base_count = l - e;
                    if ((int) (k + t) - 1 > shared_base_count) // all error distributions destroy enough k-mers
                        row.push_back(total_err_conf_count(e, l));
                    else if (e == 0)
                        row.push_back(0);
                    else
                    {
                        row.push_back(row.back() + table.back()[l - 1]);

                        size_t band = l - k - t;
                        row.back() -= table.back()[band + t - 1];

                        for (size_t i = 1; i < t; i++)
                        {
                            row.back() -= matrix[matrix.size() - i][e - 1][band + t - i - 1];
                            row.back() += matrix[matrix.size() - i][e - 1][band + t - i];
                        }
                    }
                }
                table.push_back(row);
            }
            matrix.push_back(table);
        }
        return matrix;
    }

    kmer_attributes(size_t const kmer_size, filtering_request const & request) : 
                k(kmer_size), 
                fpr(expected_kmer_occurrences(std::round(request.s / (float) request.b), kmer_size)),
                fn_conf_counts(count_err_conf_below_thresh()) 
    {
        std::cout << "Calculating FN count matrix for k=" << kmer_size << '\n'; 
    }

    double fnr_for_parameter_set(filtering_request const & request, param_set const & params) const
    {
        return fn_conf_counts[params.t - 1][request.e][request.l] / (double) request.total_conf_count;
    }
};

void runner() 
{
    size_t l = 20;
    size_t e = 3;

    uint64_t ref_size = 1024*1024*1024;
    size_t bins = 64;

    auto space = parameter_space();
    filtering_request request(e, l, ref_size, bins);
    
    std::vector<kmer_attributes> attribute_vec;
    for (auto k = std::get<0>(space.kmer_range); k <= std::get<1>(space.kmer_range); k++)
        attribute_vec.emplace_back(k, request); // call kmer_attributes constructor

    float tau{0.25};
    float mu{0.05};

    param_set best_params(attribute_vec[0].k, 1, parameter_space());
    auto best_score = attribute_vec[0].score(request, best_params);

    std::vector<std::vector<double>> scores;
    scores.reserve(std::get<1>(space.kmer_range) - std::get<0>(space.kmer_range) + 1);
    size_t i{0};

    std::cout << '\t';
    for (const auto & att : attribute_vec)
    {
        std::vector<double> kmer_scores;
        size_t k = att.k;
        for (size_t t = 1; t <= space.max_thresh; t++)
        {
            param_set params(k, t, parameter_space());
            auto score = att.score(request, params);
            kmer_scores.push_back(score);
            if (score < best_score)
            {
                best_score = score;
                best_params = params;
            }
        }
        scores.push_back(kmer_scores);
        i++;
    }

    
    std::cout << '\t';
    for (size_t t{1}; t <= scores[0].size(); t++)
        std::cout << t << '\t';
    std::cout << '\n';
    for (size_t i{0}; i < scores.size(); i++)
    {
        std::cout << std::get<0>(space.kmer_range) + i << '\t';
        for (size_t j{0}; j < scores[0].size(); j++)
        {
            std::cout << scores[i][j] << '\t';
        }
        std::cout << '\n';
    }
    std::cout << "Chose k=" << best_params.k << " and t=" <<  best_params.t << '\n';
}
