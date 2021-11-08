#pragma once

#include <chrono>
#include <future>
#include <vector>

#include <seqan3/core/debug_stream.hpp>

namespace sliding_window
{

template <typename t>
inline void do_parallel(t && worker, size_t const num_records, size_t const threads, double & compute_time)
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
        //task.wait();

        //std::set<size_t> result_set = task.get();
        auto result_set = task.get();
        for (size_t bin : result_set)
        {
            seqan3::debug_stream << std::to_string(bin) << '\t';
        }
    }
        
    auto end = std::chrono::high_resolution_clock::now();
    compute_time += std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
}

} // namespace sliding_window

