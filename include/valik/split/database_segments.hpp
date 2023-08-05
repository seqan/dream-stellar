#pragma once

#include <seqan3/core/debug_stream.hpp>
#include <seqan3/io/sequence_file/all.hpp>

#include <valik/split/database_metadata.hpp>

#include <iostream>
#include <fstream>

namespace valik
{

/** !\brief a struct that represents all segments of a reference or query database.
 *
 *  \param members      Collection of database segments.
 *  \param default_len  Default length of a segment that is dynamically updated.
 */
struct database_segments {

    /** !\brief a struct that represents a single segment.
     *
     * All indices and positions are 0-based.
     *
     *  \param id       Index of the segment in the vector of segments.
     *  \param seq_ind  Index of the underlying sequence in the input FASTA file. Corresponds to database_metadata::sequence_stats::id.
     *  \param start    Segment start position in sequence.
     *  \param len      Segment length.
     */
    struct segment {
        size_t id;
        size_t seq_ind;
        size_t start;
        size_t len;

        segment(size_t i, size_t ind, size_t s, size_t l)
        {
            id = i;
            seq_ind = ind;
            start = s;
            len = l;
        }

        std::string unique_id()
        {
            return std::to_string(seq_ind) + "_" + std::to_string(start) + "_" + std::to_string(len);
        }
    };

    std::vector<segment> members;
    size_t default_len;

    void add_segment(size_t const i, size_t const ind, size_t const s, size_t const l)
    {
        segment seg(i, ind, s, l);
        members.push_back(seg);
    }

    void construct_by_linear_scan(size_t const seg_count, size_t const overlap, database_metadata const & database)
    {
        assert(seg_count > 0);
        default_len = database.total_len / seg_count + 1;
        assert(default_len > overlap);

        size_t remaining_db_len = database.total_len;
        for (const auto & seq : database.sequences)
        {
            size_t start = 0;
            if (seq.len < (default_len / 2))
            {
                seqan3::debug_stream << "Sequence: " << seq.id << " is too short and will be skipped.\n";
                remaining_db_len -= seq.len;
            }
            else if ((seq.len >= default_len / 2) & (seq.len <= default_len * 1.5))
            {
                // database sequence is single segment
                add_segment(members.size(), seq.ind, start, seq.len);
                remaining_db_len -= seq.len;
            }
            else
            {
                // sequences that are contained in a single segment might not have the exact segment length
                // dynamically update segment length to divide the rest of the remaining database as equally as possible among the chosen number of segments
                size_t remaining_seg_count = seg_count - members.size();
                size_t updated_seg_len = remaining_db_len / remaining_seg_count;

                size_t segments_per_seq = std::round( (double) seq.len / (double) updated_seg_len);
                size_t actual_seg_len = seq.len / segments_per_seq + overlap + 1; // + 1 because integer division always rounded down

                // divide database sequence into multiple segments
                add_segment(members.size(), seq.ind, start, actual_seg_len);
                start = start + actual_seg_len - overlap;
                while (start + actual_seg_len - overlap < seq.len)
                {
                    add_segment(members.size(), seq.ind, start, actual_seg_len);
                    start = start + actual_seg_len - overlap;
                }
                add_segment(members.size(), seq.ind, start, seq.len - start);

                remaining_db_len -= seq.len;
            }
        }
        assert(members.size() == seg_count);
    }

    database_segments(size_t seg_count, size_t overlap, database_metadata const & database)
    {
        construct_by_linear_scan(seg_count, overlap, database);
    }

    // deserialize
    database_segments(std::filesystem::path filepath)
    {
        std::ifstream in_file(filepath);

        size_t id, seq_ind, start, length;
        if (in_file.is_open())
        {
            while (in_file >> id)
            {
                in_file >> seq_ind;
                in_file >> start;
                in_file >> length;

                add_segment(id, seq_ind, start, length);
            }
        }
        in_file.close();
    }

    segment segment_from_bin(size_t const id) const
    {
        for (auto & seg : members)
        {
            if (seg.id == id)
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
            out_file << seg.id << '\t' << seg.seq_ind << '\t' << seg.start << '\t' << seg.len << '\n';
        }
        out_file.close();
    }
};

} // namespace valik
