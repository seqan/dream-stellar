#pragma once

#include <chrono>
#include <future>
#include <vector>

#include <seqan3/search/dream_index/interleaved_bloom_filter.hpp>

#include <sliding_window/shared.hpp>
#include <sliding_window/search/compute_simple_model.hpp>
#include <sliding_window/search/query_result.hpp>
#include <sliding_window/search/sync_out.hpp>


namespace sliding_window::app
{

// && worker means only r-value references (temporary objects) can be passed
// which means the memory can be reallocated after the function exits
template <typename worker_t, seqan3::data_layout ibf_data_layout, typename rec_vec_t>
inline void write_output_file_parallel(worker_t && worker,
                                       seqan3::interleaved_bloom_filter<ibf_data_layout> const & ibf,
                                       search_arguments const & arguments,
                                       rec_vec_t const & records,
                                       threshold const & threshold_data,
                                       sync_out & synced_out)
{
    using task_future_t = std::future<std::vector<sliding_window::query_result>>;
    static_assert(std::same_as<task_future_t,
                               decltype(std::async(std::launch::async, worker, size_t{}, size_t{}, records, ibf, arguments, threshold_data))>);

    std::vector<task_future_t> tasks;
    size_t const num_records = records.size();
    size_t const records_per_thread = num_records / arguments.threads;

    for (size_t i = 0; i < arguments.threads; ++i)
    {
        size_t const start = records_per_thread * i;
        size_t const end = std::min(start + records_per_thread, num_records);
        tasks.emplace_back(std::async(std::launch::async, worker, start, end, records, ibf, arguments, threshold_data));
    }

    for (task_future_t & task : tasks)
    {
        // auto result_set = task.get();
        std::string result_string{};
        std::vector<query_result> thread_result = task.get();
        for (query_result const & query_result : thread_result)
        {
            result_string.clear();
            result_string += query_result.get_id();
            result_string += '\t';

            for (size_t const bin : query_result.get_hits())
            {
                result_string += std::to_string(bin);
                result_string += ',';
            }
            
            result_string += '\n';
            synced_out.write(result_string);
        }
    }
}

} // namespace sliding_window::app