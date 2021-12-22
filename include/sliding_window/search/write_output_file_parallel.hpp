#pragma once

#include <chrono>
#include <future>
#include <vector>

#include <sliding_window/search/query_result.hpp>
#include <sliding_window/search/sync_out.hpp>


namespace sliding_window
{


// && worker means only r-value references (temporary objects) can be passed
// which means the memory can be reallocated after the function exits
template <typename worker_t, typename ibf_t, typename rec_vec_t>
inline void write_output_file_parallel(worker_t && worker, ibf_t const & ibf, search_arguments const & arguments, rec_vec_t const & records, 
                            threshold const & threshold_data, sync_out & synced_out, double & compute_time)
{
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<decltype(std::async(std::launch::async, worker, size_t{}, size_t{}, ibf, arguments, records, threshold_data))> tasks;
    size_t const num_records = records.size();
    size_t const records_per_thread = num_records / arguments.threads;

    for (size_t i = 0; i < arguments.threads; ++i)
    {
        size_t const start = records_per_thread * i;
        size_t const end = i == (arguments.threads-1) ? num_records: records_per_thread * (i+1);
        tasks.emplace_back(std::async(std::launch::async, worker, start, end, ibf, arguments, records, threshold_data));
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