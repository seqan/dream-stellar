#pragma once

#include <seqan3/core/debug_stream.hpp>
#include <seqan3/io/sequence_file/all.hpp>

#include <iostream>
#include <fstream>

namespace valik
{

class reference_metadata
{
    public:
        struct sequence_stats
        {
            std::string id;
            size_t ind;
            size_t len;

            sequence_stats(std::string const ref_id, size_t const ref_ind, size_t const ref_length)
            {
                id = ref_id;
                ind = ref_ind;
                len = ref_length;
            }
        };

        uint64_t total_len;
        std::vector<sequence_stats> sequences;

        void construct_by_sequence_file(std::filesystem::path const & filepath)
        {
            using traits_type = seqan3::sequence_file_input_default_traits_dna;
            seqan3::sequence_file_input<traits_type> fin{filepath};

            total_len = 0;
            size_t ref_ind = 0;
            for (auto & record : fin)
            {
                sequence_stats seq(record.id(), ref_ind, record.sequence().size());
                total_len += seq.len;
                sequences.push_back(seq);
                ref_ind++;
            }
        }

        void construct_by_metadata_file(std::filesystem::path const & filepath)
        {
            std::ifstream in_file(filepath);

            std::string seq_id;
            size_t ref_ind, length;
            total_len = 0;
            if (in_file.is_open())
            {
                while (in_file >> seq_id)
                {
                    in_file >> ref_ind;
                    in_file >> length;
                    total_len += length;
                    sequences.push_back(sequence_stats(seq_id, ref_ind, length));
                }
            }
            in_file.close();
        }

        reference_metadata(std::filesystem::path const & filepath, bool const from_sequence)
        {
            if (from_sequence)
            {
                construct_by_sequence_file(filepath);
            }
            else
            {
                construct_by_metadata_file(filepath); // deserialize
            }
        }

        // serialize
        void to_file(std::filesystem::path filepath)
        {
            std::ofstream out_file;
            out_file.open(filepath);
            for (sequence_stats const & seq : sequences)
            {
                out_file << seq.id << '\t' << seq.ind << '\t' << seq.len << '\n';
            }
            out_file.close();
        }

};

} // namespace valik
