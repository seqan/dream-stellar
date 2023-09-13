#pragma once

#include <seqan3/argument_parser/exceptions.hpp>
#include <seqan3/core/debug_stream.hpp>
#include <seqan3/io/sequence_file/all.hpp>

#include <valik/shared.hpp>

#include <iostream>
#include <fstream>

namespace valik
{

/**
 * @brief Struct that stores the metadata for a split database.
 *  \param total_len    Total database length.
 *  \param sequences    Collection of database sequences.
 *  \param default_seg_len  Default length of a segment that is dynamically updated.
 *  \param segments     Collection of database segments.
 */
struct metadata
{
    /** !\brief a metadata struct that represents a single sequence.
     *
     * \param id    The FASTA id.
     * \param ind   0-based index in the input FASTA file.
     * \param len   Sequence length.
     */
    struct sequence_stats
    {
        std::string id;
        size_t ind;
        size_t len;

        sequence_stats(std::string const fasta_id, size_t const fasta_ind, size_t const seq_length)
        {
            id = fasta_id;
            ind = fasta_ind;
            len = seq_length;
        }
    };

    /** !\brief a struct that represents a single segment.
     *
     * All indices and positions are 0-based.
     *
     *  \param id       Index of the segment in the vector of segments.
     *  \param seq_ind  Index of the underlying sequence in the input FASTA file. Corresponds to sequence_stats::id.
     *  \param start    Segment start position in sequence.
     *  \param len      Segment length.
     */
    struct segment_stats
    {
        size_t id;
        size_t seq_ind;
        size_t start;
        size_t len;

        segment_stats(size_t i, size_t ind, size_t s, size_t l)
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

    uint64_t total_len;
    std::vector<sequence_stats> sequences;
    size_t default_seg_len;
    std::vector<segment_stats> segments;

    /**
     * @brief Function that scans over a sequence file to extract metadata.
     *
     * @param db_path Path to input file.
     */
    void scan_database_file(std::filesystem::path const & db_path)
    {
        using traits_type = seqan3::sequence_file_input_default_traits_dna;
        seqan3::sequence_file_input<traits_type> fin{db_path};
        total_len = 0;
        size_t fasta_ind = 0;
        for (auto & record : fin)
        {
            sequence_stats seq(record.id(), fasta_ind, record.sequence().size());
            total_len += seq.len;
            sequences.push_back(seq);
            fasta_ind++;
        }
    }

    void add_segment(size_t const i, size_t const ind, size_t const s, size_t const l)
    {
        segment_stats seg(i, ind, s, l);
        segments.push_back(seg);
    }

    /**
     * @brief Function that scans over the collection of sequences and greedily assigns segment positions.
     *
     * @param seg_count Number of segments.
     * @param overlap Length of overlap between adjacent segments.
     */
    void scan_database_sequences(size_t const seg_count, size_t const overlap)
    {
        assert(seg_count > 0);
        default_seg_len = total_len / seg_count + 1;
        assert(default_seg_len > overlap);

        size_t remaining_db_len = total_len;
        for (const auto & seq : sequences)
        {
            size_t start = 0;
            if (seq.len < (default_seg_len / 2))
            {
                seqan3::debug_stream << "Sequence: " << seq.id << " is too short and will be skipped.\n";
                remaining_db_len -= seq.len;
            }
            else if ((seq.len >= default_seg_len / 2) & (seq.len <= default_seg_len * 1.5))
            {
                // database sequence is single segment
                add_segment(segments.size(), seq.ind, start, seq.len);
                remaining_db_len -= seq.len;
            }
            else
            {
                // sequences that are contained in a single segment might not have the exact segment length
                // dynamically update segment length to divide the rest of the remaining database as equally as possible among the chosen number of segments
                size_t remaining_seg_count = seg_count - segments.size();
                size_t updated_seg_len = remaining_db_len / remaining_seg_count;

                size_t segments_per_seq = std::round( (double) seq.len / (double) updated_seg_len);
                size_t actual_seg_len = seq.len / segments_per_seq + overlap + 1; // + 1 because integer division always rounded down

                // divide database sequence into multiple segments
                add_segment(segments.size(), seq.ind, start, actual_seg_len);
                start = start + actual_seg_len - overlap;
                while (start + actual_seg_len - overlap < seq.len)
                {
                    add_segment(segments.size(), seq.ind, start, actual_seg_len);
                    start = start + actual_seg_len - overlap;
                }
                add_segment(segments.size(), seq.ind, start, seq.len - start);

                remaining_db_len -= seq.len;
            }
        }
        assert(segments.size() == seg_count);
    }

    /**
     * @brief Constructor that scans a sequence database to create a metadata struct.
     */
    metadata(split_arguments const & arguments)
    {
        scan_database_file(arguments.seq_file);
        scan_database_sequences(arguments.seg_count, arguments.overlap);
    }

    /**
     * @brief Constructor that deserializes a metadata struct from file.
     */
    metadata(std::filesystem::path const & filepath)
    {
        std::ifstream in_file(filepath);
        if (in_file.is_open())
        {
            std::string seq_meta;
            std::getline(in_file, seq_meta, '$');
            std::stringstream seq_str(seq_meta);

            std::string seq_id;
            size_t fasta_ind, length;
            total_len = 0;
            while (seq_str >> seq_id)
            {
                seq_str >> fasta_ind;
                seq_str >> length;
                total_len += length;
                sequences.push_back(sequence_stats(seq_id, fasta_ind, length));
            }

            std::string seg_meta;
            std::getline(in_file, seg_meta);    // newline
            std::getline(in_file, seg_meta, '$');
            std::stringstream seg_str(seg_meta);

            size_t id, seq_ind, start;
            while (seg_str >> id)
            {
                seg_str >> seq_ind;
                seg_str >> start;
                seg_str >> length;

                add_segment(id, seq_ind, start, length);
            }
        }

        in_file.close();
    }

    inline size_t ind_from_id(std::string const & string_id) const
    {
        auto it = std::find_if(sequences.begin(), sequences.end(), [&](const sequence_stats& seq) { return seq.id == string_id;});
        if (it == sequences.end())
            throw seqan3::validation_error{"Sequence metadata does not contain sequence from Stellar output."};
        else
            return (*it).ind;
    }


    //!TODO: isn't this just segments[id]???
    /**
     * @brief Function that find the segment corresponding to a numerical ID.
     *
     * @param id
     * @return segment
     */
    segment_stats segment_from_bin(size_t const id) const
    {
        /*
        for (auto & seg : segments)
        {
            if (seg.id == id)
                return seg;
        }
        */

        if (segments.size() < (id - 1))
            throw std::runtime_error{"Could not find segment"};

        return segments[id];
    }

    /**
     * @brief Function that serializes the metadata struct.
     *
     * @param filepath Output file path.
     */
    void to_file(std::filesystem::path const & filepath)
    {
        std::ofstream out_file;
        out_file.open(filepath);

        for (sequence_stats const & seq : sequences)
            out_file << seq.id << '\t' << seq.ind << '\t' << seq.len << '\n';

        out_file << "$\n";

        for (const auto & seg : segments)
            out_file << seg.id << '\t' << seg.seq_ind << '\t' << seg.start << '\t' << seg.len << '\n';

        out_file << "$\n";
        out_file.close();
    }

};

} // namespace valik
