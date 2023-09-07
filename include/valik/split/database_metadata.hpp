#pragma once

#include <seqan3/argument_parser/exceptions.hpp>
#include <seqan3/core/debug_stream.hpp>
#include <seqan3/io/sequence_file/all.hpp>

#include <iostream>
#include <fstream>

namespace valik
{

/** !\brief a metadata struct that represents a reference or query database.
 *
 *  \param total_len    Total database length.
 *  \param sequences    Collection of database sequences.
 */
struct database_metadata
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

    uint64_t total_len;
    std::vector<sequence_stats> sequences;

    void construct_by_sequence_file(std::filesystem::path const & filepath)
    {
        using traits_type = seqan3::sequence_file_input_default_traits_dna;
        seqan3::sequence_file_input<traits_type> fin{filepath};

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

    void construct_by_metadata_file(std::filesystem::path const & filepath)
    {
        std::ifstream in_file(filepath);

        std::string seq_id;
        size_t fasta_ind, length;
        total_len = 0;
        if (in_file.is_open())
        {
            while (in_file >> seq_id)
            {
                in_file >> fasta_ind;
                in_file >> length;
                total_len += length;
                sequences.push_back(sequence_stats(seq_id, fasta_ind, length));
            }
        }
        in_file.close();
    }

    database_metadata(std::filesystem::path const & filepath, bool const from_sequence)
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

    inline size_t ind_from_id(std::string const & string_id) const
    {
        auto it = std::find_if(sequences.begin(), sequences.end(), [&](const sequence_stats& seq) { return seq.id == string_id;});
        if (it == sequences.end())
            throw seqan3::validation_error{"Sequence metadata does not contain sequence from Stellar output."};
        else
            return (*it).ind;
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
