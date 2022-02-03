#pragma once

#include <seqan3/argument_parser/exceptions.hpp>
#include <seqan3/core/debug_stream.hpp>
#include <seqan3/io/sequence_file/all.hpp>

#include <valik/split/reference_metadata.hpp>

#include <iostream>
#include <fstream>

namespace valik
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

        void construct_by_linear_scan(size_t segment_len, size_t bins, size_t overlap, reference_metadata const & reference)
        {
            size_t remaining_ref_len = reference.total_len;
            size_t i = 0;
            for (const auto & seq : reference.sequences)
            {
                size_t start = 0;
                if (seq.len < (segment_len / 2))
                {
                    throw seqan3::argument_parser_error{"Reference contains sequence that is too short for the chosen segment length."};
                }
                else if ((seq.len >= segment_len / 2) & (seq.len <= segment_len * 1.5))
                {
                    // reference sequence is single segment
                    add_segment(i, seq.id, start, seq.len);
                    remaining_ref_len -= seq.len;
                    i++;
                }
                else
                {
                    // sequences that are contained in a single segment might not have exact segment length
                    // dynamically update segment length to divide the rest of the remaining reference as equally as possible along bins
                    size_t remaining_bins = bins - (i + 1);
                    size_t updated_seg_len = remaining_ref_len / remaining_bins;

                    size_t bins_per_seq = std::round( (double) seq.len / (double) updated_seg_len);
                    size_t actual_seg_len = seq.len / bins_per_seq + overlap + 1; // +1 because integer division always rounded down

                    // divide reference sequence into multiple segments
                    add_segment(i, seq.id, start, actual_seg_len);
                    i++;
                    while (start + actual_seg_len - overlap < seq.len)
                    {
                        start = start + actual_seg_len - overlap;
                        add_segment(i, seq.id, start, actual_seg_len);
                        i++;
                    }
                    start = start + actual_seg_len - overlap;
                    add_segment(i, seq.id, start, seq.len - start);
                    i++;

                    remaining_ref_len -= seq.len;
                }
            }
            assert(i == bins);
        }

        reference_segments(size_t segment_len, size_t bins, size_t overlap, reference_metadata const & reference)
        {
            default_len = segment_len;
            construct_by_linear_scan(segment_len, bins, overlap, reference);
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

} // namespace valik
