#pragma once

#include <filesystem>
#include <fstream>
#include <mutex>

#include <seqan3/core/debug_stream.hpp>
#include <seqan3/io/all.hpp>

namespace valik::app
{

class sync_out
{

public:
    sync_out() = default;
    sync_out(sync_out const &) = default;
    sync_out & operator=(sync_out const &) = default;
    sync_out(sync_out &&) = default;
    sync_out & operator=(sync_out &&) = default;
    ~sync_out() = default;

    sync_out(std::filesystem::path const & path) : file{path} {}

    template <typename t>
    void write_record(t && query_record, size_t const & bin_count)
    {
        std::string fasta_string = ">";
        fasta_string += query_record.sequence_id;
        fasta_string += '\n';
        for (auto & n : query_record.sequence)
            fasta_string += seqan3::to_char(n);
        fasta_string += '\n';

        std::lock_guard<std::mutex> lock(write_mutex);
        seqan3::debug_stream << "[Warning] Insufficient prefiltering. " << bin_count << " bins match query:\n" << fasta_string << "\n"; 
    }
    // outfile gets unlocked as soon as the current thread exits the write function

private:
    //seqan3::sequence_file_output<fields, output_format_types> fout;
    std::ofstream file;
    std::mutex write_mutex;
};

} // namespace valik::app
