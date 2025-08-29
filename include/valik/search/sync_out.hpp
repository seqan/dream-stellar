#pragma once

#include <filesystem>
#include <fstream>
#include <mutex>

#include <seqan3/io/sequence_file/output.hpp>
#include <seqan3/core/debug_stream.hpp>
#include <seqan3/io/all.hpp>

namespace valik::app
{

class sync_out
{
    using types = seqan3::type_list<seqan3::dna4_vector, std::string>;
    using fields = seqan3::fields<seqan3::field::seq, seqan3::field::id>;
    using sequence_record_type = seqan3::sequence_record<types, fields>;
    using output_format = seqan3::type_list<seqan3::format_fasta>;

public:
    sync_out() = delete; // fout
    sync_out(sync_out const &) = delete; // fout
    sync_out & operator=(sync_out const &) = delete; // fout
    sync_out(sync_out &&) = delete; // write_mutex
    sync_out & operator=(sync_out &&) = delete; // write_mutex
    ~sync_out() = default;

    sync_out(std::filesystem::path const & path) : fout{path} 
    {
        warning_message = [](size_t const bin_count, size_t const query_length)
        {
            seqan3::debug_stream << "[Warning] Insufficient prefiltering. " << bin_count << 
                                    " bins match query of length " << query_length << '\n'; 
        };
    }

    template <typename t>
    void write_warning(t && query_record, size_t const & bin_count)
    {
        std::lock_guard<std::mutex> lock(write_mutex);
        warning_message(bin_count, query_record.size());
    }
    // outfile gets unlocked as soon as the current thread exits the write function

    template <typename t>
    void write_disabled_record(t const & query_record, size_t const & bin_count, bool const verbose)
    { 
        std::lock_guard<std::mutex> lock(write_mutex);
        if (verbose)
            warning_message(bin_count, query_record.size());        
        sequence_record_type output_record{query_record.sequence, query_record.sequence_id};
        //!TODO: this causes memory error
        // fout.push_back(output_record); 
    }
    // outfile gets unlocked as soon as the current thread exits the write function

private:
    seqan3::sequence_file_output<fields, output_format> fout;
    std::function<void(size_t, size_t)> warning_message;
    std::mutex write_mutex;
};

} // namespace valik::app
