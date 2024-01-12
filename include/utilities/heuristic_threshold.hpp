#pragma once

#include <iostream>
#include <cmath>
#include <numbers>
#include <vector>

uint64_t stirling_factorial(uint64_t const n)
{
    return sqrt(2 * std::numbers::pi * n) * pow((n / std::numbers::e), (double) n);
}

uint64_t exact_factorial(uint64_t const n)
{
    uint64_t fact{1};
    for (size_t i = 2; i <= n; i++)
        fact *= i;

    return fact;
}

uint64_t factorial(uint64_t const n)
{
    if (n < 25)
        return exact_factorial(n);
    else 
        return stirling_factorial(n);
}

template <typename T>
uint64_t total_err_dist_count(T const len, T const error_count)
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

template <typename T>
std::vector<std::vector<std::vector<uint64_t>>> count_dist_below_thresh(T const kmer_size,
                                                                        T const threshold, 
                                                                        T const error_count,
                                                                        T const len)
{
    std::vector<std::vector<std::vector<uint64_t>>> matrix;
    for (T t = 1; t <= threshold; t++)
    {
        std::vector<std::vector<T>> table;
        for (T e = 0; e <= error_count; e++)
        {
            std::vector<T> row;
            for(T l = 0; l <= len; l++)
            {       
                int shared_base_count = l - e;
                if ((int) (kmer_size + t) - 1 > shared_base_count) // all error distributions destroy enough k-mers
                    row.push_back(total_err_dist_count(l, e));
                else if (e == 0)
                    row.push_back(0);
                else
                {
                    row.push_back(row.back() + table.back()[l - 1]);
                    
                    T band = l - kmer_size - t;
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

template <typename T>
void print_matrix(T const & matrix)
{
    for (auto table : matrix)
    {
        std::cout << "\t";
        for (size_t l = 0; l < table[0].size(); l++)
        {
            std::cout << l << '\t';
        }
        std::cout << '\n';

        for (size_t e = 0; e < table.size(); e++)
        {
            std::cout << e << '\t';
            for (size_t l = 0; l < table[e].size(); l++)
            {
                auto cell = table[e][l];
                std::cout << cell << '\t';
            }
            std::cout << '\n';
        }
    }
}

template <typename T>
float false_neg_rate(std::vector<std::vector<std::vector<uint64_t>>> const & matrix,
                     T const threshold, 
                     T const error_count)
{
    T len = matrix[0][0].size() - 1;
    auto dist_count = total_err_dist_count(len, error_count);

    return matrix[threshold - 1][error_count].back() / (double) dist_count ;   
}

void print_FNR(size_t const k, size_t const e, size_t const l, size_t const max_thresh)
{
    auto matrix = count_dist_below_thresh(k, max_thresh, e, l);

    std::cout.precision(3);
    std::cout << "threshold\tFN\tover threshold\n";
    for (size_t t = 1; t <= max_thresh; t++)
        std::cout << t << '\t' 
                  << 100 * false_neg_rate(matrix, t, e) << "%\t"
                  << total_err_dist_count(l, e) - matrix[t - 1][e].back() << '\n';

}
