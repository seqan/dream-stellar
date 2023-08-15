#pragma once

#include <chrono>
#include <thread>

#include <seqan3/search/dream_index/interleaved_bloom_filter.hpp>
#include <seqan3/core/debug_stream.hpp>

#include <valik/shared.hpp>
#include <valik/search/local_prefilter.hpp>
#include <valik/search/query_record.hpp>
#include <valik/search/sync_out.hpp>

#include <raptor/threshold/threshold.hpp>

#include "utilities/cart_queue.hpp"

namespace valik::app
{

template <typename query_t, seqan3::data_layout ibf_data_layout>
inline void prefilter_queries_parallel(seqan3::interleaved_bloom_filter<ibf_data_layout> const & ibf,
                                       search_arguments const & arguments,
                                       std::vector<query_t> const & records,
                                       raptor::threshold::threshold const & thresholder,
                                       cart_queue<query_t> & queue)
{
    if (records.empty())
        return;

    std::vector<std::jthread> tasks;
    size_t const num_records = records.size();
    size_t const records_per_thread = num_records / arguments.threads;

    for (size_t i = 0; i < arguments.threads; ++i)
    {
        size_t const start = records_per_thread * i;
        size_t const end = i == (unsigned) (arguments.threads - 1) ? num_records : records_per_thread * (i + 1);

        std::span<query_t const> records_slice{&records[start], &records[end]};

        auto result_cb = [&queue](query_t const& record, std::unordered_set<size_t> const& bin_hits)
        {
            for (size_t const bin : bin_hits)
            {
                /*


                seqan3::debug_stream << "Cart insertion of sequence: " << '\n';
                for (auto & n : record.sequence)
                    seqan3::debug_stream << n;
                seqan3::debug_stream << '\n';
                */
                queue.insert(bin, record);
            }
        };

        // The following calls `local_prefilter(records, ibf, arguments, threshold)` on a thread.
        tasks.emplace_back([=, &ibf, &arguments, &thresholder]()
        {
            local_prefilter(records_slice, ibf, arguments, thresholder, result_cb);
        });
    }
}

} // namespace valik::app
