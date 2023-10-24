#pragma once

#include <filesystem>
#include <fstream>
#include <mutex>

#include <seqan3/io/all.hpp>

namespace valik::app
{

class sync_out
{

using types = seqan3::type_list<std::vector<seqan3::dna4>, std::string>;
using fields = seqan3::fields<seqan3::field::seq, seqan3::field::id>;
using sequence_record_type = seqan3::sequence_record<types, fields>;
using output_format_types = seqan3::type_list<seqan3::format_fasta>;

public:
    sync_out() = default;
    sync_out(sync_out const &) = default;
    sync_out & operator=(sync_out const &) = default;
    sync_out(sync_out &&) = default;
    sync_out & operator=(sync_out &&) = default;
    ~sync_out() = default;

    sync_out(std::filesystem::path const & path) : fout{path} {}

    template <typename t>
    void write_record(t && query_record)
    {
        sequence_record_type fasta_record{std::move(query_record.sequence), std::move(query_record.sequence_id)}; 
        std::lock_guard<std::mutex> lock(write_mutex);
        fout.push_back(fasta_record);
    }
    // outfile gets unlocked as soon as the current threads exits the write function

private:
    seqan3::sequence_file_output<fields, output_format_types> fout;
    std::mutex write_mutex;
};

} // namespace valik::app
