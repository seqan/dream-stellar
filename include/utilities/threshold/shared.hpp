#pragma once

#include <iostream>
#include <fstream>
#include <cmath>
#include <numbers>
#include <vector>
#include <utility>
#include <filesystem>

namespace valik
{

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
    constexpr uint8_t alphabet_size{4};
    return (float) (bin_size - kmer_size + 1) / (float) pow(alphabet_size, kmer_size);
}

/**
 * @brief K-mer lemma threhold.
*/
template <typename var_t>
var_t kmer_lemma_threshold(size_t const l, var_t const k, var_t const e)
{
    if ((l - k + 1) <= e*k)
        return 0;
    
    return l - k + 1 - e * k;
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
    constexpr static uint8_t max_thresh{5};
    constexpr static size_t max_len{150};
    constexpr static std::pair<uint8_t, uint8_t> kmer_range{9, 21};
};

/**
 * @brief Number of combinations of n take k.
 * 
 * Same as the number of different error configurations if n=sequence length and k=error_count. 
*/
template <typename par_t, typename val_t>
val_t combinations(par_t const k, size_t const n)
{
    if (n >= k)
    {
        val_t combinations{1};
        for (size_t i = n - k + 1; i <= n; i++)
            combinations *= i;
        combinations = combinations / factorial(k);
        return combinations;   // same as (uint64_t) (factorial(n) / (factorial(n - k) * factorial(k)));
    }
    else
        return (val_t) 0;
}

}   //namespace valik

