#pragma once

#include <seqan3/core/debug_stream.hpp>
#include <seqan3/io/sequence_file/all.hpp>

#include <iostream>
#include <fstream>

namespace sliding_window
{

class reference_metadata
{
    public:
        struct sequence_stats 
        {
            std::string id;             
            size_t len;

            sequence_stats(std::string ref_id, size_t ref_length)
            {
                id = ref_id;
                len = ref_length;
            }        
        };

        size_t total_len;
        std::vector<sequence_stats> sequences;

        reference_metadata(std::filesystem::path filepath, bool from_sequence) 
        { 
            if (from_sequence)
            {
                using traits_type = seqan3::sequence_file_input_default_traits_dna;
                seqan3::sequence_file_input<traits_type> fin{filepath};

                total_len = 0;
                for (auto & record : fin)
                {
                    sequence_stats seq(record.id(), record.sequence().size());
                    total_len += seq.len;
                    sequences.push_back(seq);
                }
            }
            else // deserialize
            {
                std::ifstream in_file(filepath);

                std::string seq_id;
                size_t length;
                total_len = 0;
                if (in_file.is_open())
                {
                    while (in_file >> seq_id)
                    {
                        in_file >> length;
                        total_len += length;
                        sequences.push_back(sequence_stats(seq_id, length));
                    }
                }
                in_file.close();
            }
        }

        // serialize
        void to_file(std::filesystem::path filepath)
        {
            std::ofstream out_file;
            out_file.open(filepath);
            for (sequence_stats & seq : sequences)
            {
                out_file << seq.id << '\t' << seq.len << '\n';
            }
            out_file.close();
        }

};

} // namespace sliding_window