#pragma once

#include <valik/search/minimiser_model.hpp>
#include <valik/shared.hpp>

namespace valik
{

inline std::vector<size_t> compute_simple_model(search_arguments const & arguments)
{
    std::vector<size_t> precomp_thresholds;

    if (!arguments.threshold && !do_cerealisation_in(precomp_thresholds, arguments))
    {
        precomp_thresholds = precompute_threshold(arguments.pattern_size,
                                                  arguments.window_size,
                                                  arguments.shape_size,
                                                  arguments.errors,
                                                  arguments.tau);

        do_cerealisation_out(precomp_thresholds, arguments);
    }

    return precomp_thresholds;
}

// struct constructor did not work
struct threshold
{
    size_t kmers_per_window;
    size_t kmers_per_pattern;
    size_t min_number_of_minimisers;
    size_t kmer_lemma;
    size_t max_number_of_minimisers;
    std::vector<size_t> precomp_thresholds;
};

inline threshold make_threshold_data(search_arguments const & arguments)
{
    auto threshold_data = threshold{};

    uint8_t kmer_size = arguments.shape_size;
    threshold_data.kmers_per_window = arguments.window_size - kmer_size + 1;
    threshold_data.kmers_per_pattern = arguments.pattern_size - kmer_size + 1;
    threshold_data.min_number_of_minimisers = threshold_data.kmers_per_window == 1 ?
                    threshold_data.kmers_per_pattern : std::ceil(threshold_data.kmers_per_pattern / static_cast<double>(threshold_data.kmers_per_window));
    threshold_data.kmer_lemma = arguments.pattern_size + 1u > (arguments.errors + 1u) * kmer_size ?
                    arguments.pattern_size + 1u - (arguments.errors + 1u) * kmer_size : 0;
    threshold_data.max_number_of_minimisers = arguments.pattern_size - arguments.window_size + 1;
    threshold_data.precomp_thresholds = compute_simple_model(arguments);

    return threshold_data;
}

} // namespace valik
