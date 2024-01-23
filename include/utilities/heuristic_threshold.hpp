#pragma once

#include <iostream>
#include <fstream>
#include <cmath>
#include <numbers>
#include <vector>
#include <utility>
#include <filesystem>

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

/**
 * @brief Factorial of integer n. 
*/
template <typename val_t>
val_t factorial(val_t const n)
{
    if (n < 25)
        return exact_factorial(n);
    else 
        return stirling_factorial(n);
}

/**
 *  @brief Assuming k-mers are distributed uniformly randomly, what is the expected count of a k-mer in a bin.
 * 
 * @param bin_size Size of reference segment in bases.
 * @param kmer_size K-mer size.
 * 
*/
template <typename var_t, typename par_t>
float expected_kmer_occurrences(var_t const & bin_size,
                               par_t const & kmer_size)
{
    constexpr size_t alphabet_size{4};
    return (float) (bin_size - kmer_size + 1) / (float) pow(alphabet_size, kmer_size);
}

/**
 * @brief Definition of the search space for the parameter tuning algorithm.
 * 
 * @param max_errors Maximum number of errors.
 * @param max_thresh Maximum thershold for the number of k-mers that are shared after introducing errors.
 * @param max_len The highest minimum local match length to consider.
 * @param kmer_range The range of k-mer sizes.
*/
struct parameter_space
{
    constexpr static size_t max_errors{3};    
    constexpr static size_t max_thresh{3};
    constexpr static size_t max_len{20};
    constexpr static std::pair<size_t, size_t> kmer_range{9, 15};
};

/**
 * @brief Total number of error configurations. Same as the number of combinations of len take error_count. 
 * 
 * @param error_count Number of errors.
 * @param len Sequence length.
*/
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

/**
 * @brief For a kmer size k consider how the FNR changes for various values of the parameters t, e and l. 
 *   
 * @param k Chosen k-mer size.
 * @param fn_conf_counts Number of configurations of e errors that do not retain at least t shared kmers after mutation.
*/
struct kmer_attributes
{
    using row_t = std::vector<uint64_t>;
    using table_t = std::vector<row_t>;
    using mat_t = std::vector<table_t>;
    
    const size_t k;
    const mat_t fn_conf_counts;  // false negative configuration counts

    /**
     * @brief For a maximum error count find the number of error configurations 
     *        that do not retain at least the threshold number of k-mers after mutation.
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

    kmer_attributes(size_t const kmer_size) : 
                k(kmer_size), 
                fn_conf_counts(count_err_conf_below_thresh()) { }

    kmer_attributes(size_t const kmer_size, mat_t const & matrix) : k(kmer_size), fn_conf_counts(matrix) {}

    /**
     * @brief False negative rate for a parameter set.
    */
    double fnr_for_param_set(filtering_request const & request, param_set const & params) const
    {
        return fn_conf_counts[params.t - 1][request.e][request.l] / (double) request.total_conf_count();
    }

    /**
     * @brief Score of the objective function for a parameter set. Smaller values are better.
    */
    double score(filtering_request const & request, param_set const & params) const
    {
        return fnr_for_param_set(request, params) + pow(request.fpr(k), params.t);
    }

    /**
     * @brief Stream out flattened 3D matrix of false negative configuration counts.
    */
    template <typename str_t>
    void serialize(str_t & outstr)
    {
        outstr << "k=" << k << '\n'; 
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
};

/**
 * @brief Precalculate and write out FN configuration count tables.
*/
void write_precalc_fn_confs(std::filesystem::path const & outfile)
{
    auto space = parameter_space();
    for (auto k = std::get<0>(space.kmer_range); k <= std::get<1>(space.kmer_range); k++)
    {
        kmer_attributes attr(k);
        std::ofstream outstr;
        outstr.open(outfile, std::ios_base::app);
        attr.serialize(outstr);
    }
}

/**
 * @brief Deserialize kmer_attributes for a single k-mer size.
*/
kmer_attributes deserialize_kmer_attributes(std::string const & kmer_attr_str)
{
    std::istringstream matrix_str(kmer_attr_str);
    std::string line;
    std::getline(matrix_str, line);
    size_t k = stoi(line.substr(line.find("k=") + 2));
        
    std::vector<std::vector<std::vector<uint64_t>>> matrix;
    std::vector<std::vector<uint64_t>> table;
    for (; std::getline(matrix_str, line); )
    {
        std::istringstream row_str(line);
        if (line.find("t=") == std::string::npos)
        {
            std::string cell;
            std::vector<uint64_t> row;
            for (; std::getline(row_str, cell, '\t'); )
            {
                row.push_back(stoi(cell));
            }
            table.push_back(row);
        }
        else if (stoi(line.substr(line.find("t=") + 2)) == 1)
        {
            continue;
        }
        else
        {
            matrix.push_back(table);
            table.clear();
        }
    }
    
    matrix.push_back(table);
    return kmer_attributes(k, matrix);
}

/**
 * @brief Read precalculated FN error configuration count tables across all k-mer sizes. 
*/
std::vector<kmer_attributes> read_fn_confs(std::filesystem::path const & infile)
{
    std::ifstream instr(infile);

    std::string line;
    std::string kmer_attr_str;
    std::vector<kmer_attributes> attr_vec;
    bool past_first(false);
    while (std::getline(instr, line)) 
    {
        if (line.find("k=") != std::string::npos)
        {
            if (past_first)
            {
                attr_vec.push_back(deserialize_kmer_attributes(kmer_attr_str));
                kmer_attr_str.clear();
            }
            past_first = true;
        }
        kmer_attr_str += line + '\n';
    }

    return attr_vec;
}

void runner() 
{
    std::string outfile = "outfile.tsv";
    write_precalc_fn_confs(outfile);

    auto attribute_vec = read_fn_confs(outfile);
    
    auto space = parameter_space();

    size_t l = 20;
    size_t e = 3;

    uint64_t ref_size = 1024*1024*1024;
    size_t bins = 64;

    filtering_request request(e, l, ref_size, bins);
    param_set best_params(attribute_vec[0].k, 1, space);
    auto best_score = attribute_vec[0].score(request, best_params);

    std::vector<std::vector<double>> scores;
    std::vector<std::vector<double>> fn_rates;
    std::vector<double> fp_rates;
    scores.reserve(std::get<1>(space.kmer_range) - std::get<0>(space.kmer_range) + 1);
    fn_rates.reserve(std::get<1>(space.kmer_range) - std::get<0>(space.kmer_range) + 1);
    fp_rates.reserve(std::get<1>(space.kmer_range) - std::get<0>(space.kmer_range) + 1);
    size_t i{0};

    std::cout << '\t';
    for (const auto & att : attribute_vec)
    {
        std::vector<double> kmer_scores;
        std::vector<double> kmer_fn;
        size_t k = att.k;
        for (size_t t = 1; t <= space.max_thresh; t++)
        {
            param_set params(k, t, parameter_space());
            auto score = att.score(request, params);
            kmer_scores.push_back(score);
            kmer_fn.push_back(att.fnr_for_param_set(request, params));
            if (score < best_score)
            {
                best_score = score;
                best_params = params;
            }
        }
        scores.push_back(kmer_scores);
        fn_rates.push_back(kmer_fn);
        fp_rates.push_back(request.fpr(att.k));
        i++;
    }

    std::cout << '\t';
    for (size_t t{1}; t <= scores[0].size(); t++)
        std::cout << "t=" << t << '\t';
    std::cout << "FPR" << '\n';
    for (size_t i{0}; i < scores.size(); i++)
    {
        std::cout << "k=" << std::get<0>(space.kmer_range) + i << '\t';
        for (size_t j{0}; j < scores[0].size(); j++)
        {
            std::cout << fn_rates[i][j] << '\t';
        }
        std::cout << '\t' << fp_rates[i] << '\n';
    }
    std::cout << "Chose k=" << best_params.k << " and t=" <<  best_params.t << '\n';
}
