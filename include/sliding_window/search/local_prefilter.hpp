#pragma once

#include <vector>
#include <seqan3/std/span>

#include <seqan3/search/dream_index/interleaved_bloom_filter.hpp>

#include <sliding_window/search/compute_simple_model.hpp> // threshold
#include <sliding_window/search/query_record.hpp>
#include <sliding_window/search/query_result.hpp>
#include <sliding_window/shared.hpp> // search_arguments

namespace sliding_window
{

struct local_prefilter_fn
{
    // NOTE: definition is in include/sliding_window/search/search_setup.hpp
    // TODO: move definition into this file
    template <seqan3::data_layout ibf_data_layout>
    std::vector<query_result>
    operator()(std::span<query_record const> const & records,
               seqan3::interleaved_bloom_filter<ibf_data_layout> const & ibf,
               search_arguments const & arguments,
               threshold const & threshold_data) const;
};

static constexpr local_prefilter_fn local_prefilter{};

} // namespace sliding_window
