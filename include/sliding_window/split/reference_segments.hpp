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
                size_t bin;
                std::string ref_id;
                size_t start;
                size_t len;

            segment(size_t b, std::string id, size_t s, size_t l)
            {
                bin = b;
                ref_id = id;
                start = s;
                len = l;
            }
        };

        std::vector<segment> members;
        size_t default_len;

        void add_segment(size_t b, std::string id, size_t s, size_t l)
        {
            segment seg(b, id, s, l);
            members.push_back(seg);
        }

        void construct_by_linear_scan(size_t segment_len, size_t overlap, auto & reference_sequences)
        {
            size_t i = 0;
            for (const auto & seq : reference_sequences)
            {
                size_t start = 0;

                // only one segment per reference sequence
                if (start + segment_len >= seq.len)
                {
                    add_segment(i, seq.id, start, seq.len);
                    i++;
                }

                // many segments per reference sequence
                else
                {
                    add_segment(i, seq.id, start, segment_len);
                    i++;
                    while (start + segment_len < seq.len)
                    {
                        start = start + segment_len - overlap;
                        add_segment(i, seq.id, start, segment_len);
                        i++;
                    }
                    add_segment(i, seq.id, start, seq.len - start);
                    i++;
                }
            }
        }

        reference_segments(size_t segment_len, size_t overlap, auto & reference_sequences)
        {
            default_len = segment_len;
            construct_by_linear_scan(segment_len, overlap, reference_sequences);
        }

        // deserialize
        reference_segments(std::filesystem::path filepath)
        {
            std::ifstream in_file(filepath);

            size_t bin, start, length;
            std::string ref_id;
            if (in_file.is_open())
            {
                in_file >> default_len;
                while (in_file >> bin)
                {
                    in_file >> ref_id;
                    in_file >> start;
                    in_file >> length;

                    add_segment(bin, ref_id, start, length);
                }
            }
            in_file.close();
        }

        // serialize
        void to_file(std::filesystem::path filepath)
        {
            std::ofstream out_file;
            out_file.open(filepath);

            out_file << default_len << '\n';
            for (const auto & seg : members)
            {
                out_file << seg.bin << '\t' << seg.ref_id << '\t' << seg.start << '\t' << seg.len << '\n';
            }
            out_file.close();
        }
};

} // namespace sliding_window
