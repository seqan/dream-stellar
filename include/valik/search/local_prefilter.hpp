#pragma once

#include <vector>
#include <seqan3/std/span>

#include <seqan3/search/dream_index/interleaved_bloom_filter.hpp>

#include <valik/search/compute_simple_model.hpp> // threshold
#include <valik/search/query_record.hpp>
#include <valik/search/query_result.hpp>
#include <valik/shared.hpp> // search_arguments

namespace valik
{

struct local_prefilter_fn
{
    // NOTE: definition is in include/valik/search/search_setup.hpp
    // TODO: move definition into this file
    template <seqan3::data_layout ibf_data_layout>
    std::vector<query_result>
    operator()(std::span<query_record const> const & records,
               seqan3::interleaved_bloom_filter<ibf_data_layout> const & ibf,
               search_arguments const & arguments,
               threshold const & threshold_data) const;
};

static constexpr local_prefilter_fn local_prefilter{};

} // namespace valik
