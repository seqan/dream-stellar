#pragma once

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
                size_t ref_ind;
                size_t start;
                size_t len;

            segment(size_t b, size_t ind, size_t s, size_t l)
            {
                bin = b;
                ref_ind = ind;
                start = s;
                len = l;
            }

            std::string unique_id()
            {
                return std::to_string(ref_ind) + "_" + std::to_string(start) + "_" + std::to_string(len);
            }
        };

        std::vector<segment> members;
        size_t default_len;

        void add_segment(size_t const b, size_t const ind, size_t const s, size_t const l)
        {
            segment seg(b, ind, s, l);
            members.push_back(seg);
        }

        void construct_by_linear_scan(size_t const bins, size_t const overlap, reference_metadata const & reference)
        {
            assert(bins > 0);
            default_len = reference.total_len / bins + 1;
            assert(default_len > overlap);

            size_t remaining_ref_len = reference.total_len;
            for (const auto & seq : reference.sequences)
            {
                size_t start = 0;
                if (seq.len < (default_len / 2))
                {
                    seqan3::debug_stream << "Reference sequence: " << seq.id << " is too short and will be skipped.\n";
                    remaining_ref_len -= seq.len;
                }
                else if ((seq.len >= default_len / 2) & (seq.len <= default_len * 1.5))
                {
                    // reference sequence is single segment
                    add_segment(members.size(), seq.ind, start, seq.len);
                    remaining_ref_len -= seq.len;
                }
                else
                {
                    // sequences that are contained in a single segment might not have the exact segment length
                    // dynamically update segment length to divide the rest of the remaining reference as equally as possible along bins
                    size_t remaining_bins = bins - members.size();
                    size_t updated_seg_len = remaining_ref_len / remaining_bins;

                    size_t bins_per_seq = std::round( (double) seq.len / (double) updated_seg_len);
                    size_t actual_seg_len = seq.len / bins_per_seq + overlap + 1; // + 1 because integer division always rounded down

                    // divide reference sequence into multiple segments
                    add_segment(members.size(), seq.ind, start, actual_seg_len);
                    start = start + actual_seg_len - overlap;
                    while (start + actual_seg_len - overlap < seq.len)
                    {
                        add_segment(members.size(), seq.ind, start, actual_seg_len);
                        start = start + actual_seg_len - overlap;
                    }
                    add_segment(members.size(), seq.ind, start, seq.len - start);

                    remaining_ref_len -= seq.len;
                }
            }
            assert(members.size() == bins);
        }

        reference_segments(size_t bins, size_t overlap, reference_metadata const & reference)
        {
            construct_by_linear_scan(bins, overlap, reference);
        }

        // deserialize
        reference_segments(std::filesystem::path filepath)
        {
            std::ifstream in_file(filepath);

            size_t bin, ref_ind, start, length;
            if (in_file.is_open())
            {
                while (in_file >> bin)
                {
                    in_file >> ref_ind;
                    in_file >> start;
                    in_file >> length;

                    add_segment(bin, ref_ind, start, length);
                }
            }
            in_file.close();
        }

        segment segment_from_bin(size_t const bin) const
        {
            for (auto & seg : members)
            {
                if (seg.bin == bin)
                    return seg;
            }

            throw std::runtime_error{"Could not find segment"};
        }

        // serialize
        void to_file(std::filesystem::path filepath)
        {
            std::ofstream out_file;
            out_file.open(filepath);

            for (const auto & seg : members)
            {
                out_file << seg.bin << '\t' << seg.ref_ind << '\t' << seg.start << '\t' << seg.len << '\n';
            }
            out_file.close();
        }
};

} // namespace valik
