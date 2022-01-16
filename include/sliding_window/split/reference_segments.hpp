#pragma once

#include <seqan3/core/debug_stream.hpp>
#include <seqan3/io/sequence_file/all.hpp>

#include <iostream>
#include <fstream>

namespace sliding_window
{

class reference_segments {
    public: 
        class segment {
            public:
                std::string ref_id;
                size_t start;
                size_t len;
                size_t bin;

            segment(std::string id, size_t s, size_t l, size_t b) { // Constructor with parameters
                ref_id = id;
                start = s;
                len = l;
                bin = b;
            }
        };

        std::vector<segment> members;
        size_t default_len;

        void add_segment(std::string id, size_t s, size_t l, size_t b)
        {
            segment seg(id, s, l, b);
            members.push_back(seg);
        }

        reference_segments(size_t segment_len, size_t overlap, auto & reference_sequences)
        {
            default_len = segment_len;
            size_t i = 0;
            for (const auto & seq : reference_sequences)
            {
                size_t start = 0;

                // only one segment per reference sequence
                if (start + segment_len >= seq.len)
                {
                    add_segment(seq.id, start, seq.len, i);
                    i++;
                } 
                
                // many segments per reference sequence
                else 
                {
                    add_segment(seq.id, start, segment_len, i);
                    i++;
                    while (start + segment_len < seq.len)
                    {
                        start = start + segment_len - overlap;
                        add_segment(seq.id, start, segment_len, i);
                        i++;
                    }
                    add_segment(seq.id, start, seq.len - start, i);
                    i++;
                }
            }
        }

        void to_file(std::string filepath)
        {
            std::ofstream out_file;
            out_file.open(filepath);
            out_file << "(default) LENGTH: " << default_len << '\n';

            out_file << "BIN" << '\t' << "REF ID" << '\t' << "START" << '\t' << "LEN" << '\n';
            for (const auto & seg : members)
            {
                out_file << seg.bin << '\t' << seg.ref_id << '\t' << seg.start << '\t' << seg.len << '\n';
            }
            out_file.close();
        }
};

} // namespace sliding_window