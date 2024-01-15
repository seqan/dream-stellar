#pragma once

#include <iostream>
#include <cmath>
#include <numbers>
#include <vector>

template <typename val_t>
val_t stirling_factorial(val_t const n)
{
    return sqrt(2 * std::numbers::pi * n) * pow((n / std::numbers::e), (double) n);
}

template <typename val_t>
val_t exact_factorial(val_t const n)
{
    T fact{1};
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

template <typename par_t, typename val_t>
val_t total_err_dist_count(par_t const len, par_t const error_count)
{
    if (len >= error_count)
    {
        val_t combinations{1};
        for (par_t i = len - error_count + 1; i <= len; i++)
            combinations *= i;
        combinations = combinations / factorial(error_count);
        return combinations;   // same as (uint64_t) (factorial(len) / (factorial(len - error_count) * factorial(error_count)));
    }
    else
        return (val_t) 0;
}

/**
 * @brief For a maximum error count find the number of error configurations 
 *        that do not retain at least the threshold number of k-mers after mutation.
 * 
 * @param kmer_size K-mer length.
 * @param threshold Minimum number of shared k-mers for success.
 * @param error_count Number of errors.
 * @param len Length of sequences being compared.
*/
template <typename par_t, typename val_t>
std::vector<std::vector<std::vector<val_t>>> count_err_conf_below_thresh(par_t const kmer_size,
                                                                         par_t const threshold, 
                                                                         par_t const error_count,
                                                                         par_t const len)
{
    std::vector<std::vector<std::vector<val_t>>> matrix;
    for (par_t t = 1; t <= threshold; t++)
    {
        std::vector<std::vector<val_t>> table;
        for (par_t e = 0; e <= error_count; e++)
        {
            std::vector<val_t> row;
            for(par_t l = 0; l <= len; l++)
            {       
                int shared_base_count = l - e;
                if ((int) (kmer_size + t) - 1 > shared_base_count) // all error distributions destroy enough k-mers
                    row.push_back(total_err_dist_count(l, e));
                else if (e == 0)
                    row.push_back(0);
                else
                {
                    row.push_back(row.back() + table.back()[l - 1]);
                    
                    par_t band = l - kmer_size - t;
                    row.back() -= table.back()[band + t - 1];
                    
                    for (par_t i = 1; i < t; i++)
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

template <typename vec_t, typename par_t>
void print_matrix(vec_t const & matrix)
{
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
 * @brief Assess the FNR from shared k-mer distribution.
 * 
 * @param matrix The number of error distributions that invalidate shared k-mers for different sequence lengths and error counts.
 * @param threshold The expected number of shared k-mers after mutation.
 * @param error_count The number of errors introduced.#
 * 
 * @tparam par_t Small int type for command line parameters.
 * @tparam val_t Large int type for counting error distributions.
 * 
*/
template <typename par_t, typename val_t>
float false_neg_rate(std::vector<std::vector<std::vector<val_t>>> const & matrix,
                     par_t const threshold, 
                     par_t const error_count)
{
    T len = matrix[0][0].size() - 1;
    auto dist_count = total_err_dist_count(len, error_count);

    return matrix[threshold - 1][error_count].back() / (double) dist_count;
}

template <typename par_t>
void print_FNR(par_t const k, par_t const e, par_t const l, par_t const max_thresh)
{
    auto matrix = count_dist_below_thresh(k, max_thresh, e, l);

    std::cout.precision(3);
    std::cout << "threshold\tFN\tover threshold\n";
    for (par_t t = 1; t <= max_thresh; t++)
        std::cout << t << '\t' 
                  << 100 * false_neg_rate(matrix, t, e) << "%\t"
                  << total_err_dist_count(l, e) - matrix[t - 1][e].back() << '\n';
}
