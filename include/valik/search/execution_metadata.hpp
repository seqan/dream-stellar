#pragma once

#include "sstream"

#include <seqan3/core/debug_stream.hpp>

#include <valik/search/search_time_statistics.hpp>
#include <valik/shared.hpp>

namespace valik::app
{

struct execution_metadata
{
    struct thread_metadata
    {
        std::vector<std::string> output_files;
        std::stringstream        text_out;
        std::vector<double>      time_statistics;
    };

    execution_metadata(size_t const & threads)
    {
        table = std::vector<thread_metadata>(threads);
    }

    void merge(search_arguments const & arguments,
               search_time_statistics & time_statistics) // IN-OUT parameter
    {
        // Merge all local data together
        std::ofstream text_out(arguments.out_file.string() + ".out");
        for (auto const& td : table)
        {
            output_files.insert(output_files.end(), td.output_files.begin(), td.output_files.end());
            time_statistics.cart_processing_times.insert(time_statistics.cart_processing_times.end(), td.time_statistics.begin(), td.time_statistics.end());
            if (arguments.verbose)
                text_out << td.text_out.str();
        }
    }

    std::vector<thread_metadata> table;
    std::vector<std::string> output_files;
    std::unordered_map<size_t, size_t> bin_count; // <bin_id, carts_per_bin>
};

}   // namespace valik::app
