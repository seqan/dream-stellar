#include <seqan3/core/debug_stream.hpp>
#include <seqan3/io/sequence_file/all.hpp>

class reference_metadata
{
    public:
        struct sequence_stats 
        {
            std::string id;             
            uint32_t len;        
        };

        uint64_t total_len;
        std::vector<sequence_stats> sequences;

        reference_metadata(std::string filename) 
        { 
            using traits_type = seqan3::sequence_file_input_default_traits_dna;
            seqan3::sequence_file_input<traits_type> fin{filename};

            total_len = 0;
            for (auto & record : fin)
            {
                sequence_stats seq;
                seq.id = record.id();
                seq.len = record.sequence().size();
                sequences.push_back(seq);
                total_len += seq.len;
            }
        }

        void print_metadata()
        {
            seqan3::debug_stream << "------------------- REFERENCE METADATA -------------------" << '\n';
            seqan3::debug_stream << "ID" << '\t' << "LEN" << '\n';

            for (sequence_stats & seq : sequences)
            {
                seqan3::debug_stream << seq.id << '\t' << seq.len << '\n';
            }

            seqan3::debug_stream << "TOTAL LEN: " << total_len << '\n';
        }

};