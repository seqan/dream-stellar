#pragma once

#include <chrono>
#include <future>
#include <vector>

#include <seqan3/core/debug_stream.hpp>

#include <sliding_window/search/query_result.hpp>
#include <sliding_window/search/sync_out.hpp>

namespace sliding_window
{

template <typename t>
// && worker means only r-value references (temporary objects) can be passed 
// which means the memory can be reallocated after the function exits
inline void do_parallel(t && worker, size_t const num_records, sync_out & synced_out, size_t const threads, double & compute_time)
{
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<decltype(std::async(std::launch::async, worker, size_t{}, size_t{}))> tasks; // std::async returns a std::future
    size_t const records_per_thread = num_records / threads;

    for (size_t i = 0; i < threads; ++i)
    {
        size_t const start = records_per_thread * i;
        size_t const end = i == (threads-1) ? num_records: records_per_thread * (i+1);
        tasks.emplace_back(std::async(std::launch::async, worker, start, end));
    }

    for (auto && task : tasks)
    {
        // auto result_set = task.get();
        std::string result_string{};
        std::vector<query_result> thread_result = task.get();
        for (auto query_result : thread_result)
        {
            result_string.clear();
            result_string += query_result.get_id();
            result_string += '\t';
                
            for (auto bin : query_result.get_hits())
            {
                result_string += std::to_string(bin);
                result_string += ',';
            }
            result_string += '\n';
            synced_out.write(result_string);
        }
    }
        
    auto end = std::chrono::high_resolution_clock::now();
    compute_time += std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
}

} // namespace sliding_window

