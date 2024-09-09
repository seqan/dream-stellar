#pragma once

#include <filesystem>
#include <span>

#include <dream_stellar/io/import_sequence.hpp>
#include <utilities/alphabet_wrapper/seqan/alphabet.hpp>
#include <valik/search/query_record.hpp>

#include <seqan3/io/sequence_file/output.hpp>
#include <seqan3/io/sequence_file/record.hpp>
#include <seqan3/core/debug_stream.hpp>

namespace valik
{

/**
 *  \brief Extract the segment sequences from shared query records. 
 *
 *  \param records vector containing valik split query segments
 *  \param seqs set of query segments (in-out)
 *  \param ids set of query segment ids (in-out)
 *  \param strOut stream for standard output
 */
template <typename alphabet_t, typename str_t>
inline bool get_cart_queries(std::vector<shared_query_record<alphabet_t>> const & records,
                             std::vector<std::span<alphabet_t const>> & seqs,
                             std::vector<std::string> & ids, 
                             str_t & str_out)
{
    std::set<std::string> uniqueIds; // set of short IDs (cut at first whitespace)

    size_t seq_count{0};
    for (auto & record : records)
    {
        seqs.emplace_back(record.sequence());
        ids.emplace_back(record.id());
        seq_count++;
    }

    str_out << "Loaded " << seq_count << " query sequence" << ((seq_count > 1) ? "s " : " ") << "from cart." << std::endl;
    return true;
}

/**
 *  \brief Function that writes out cart queries.
 *
 *  \param records vector containing query segments
 *  \param cart_queries_path output path
 */
template <typename rec_vec_t>
void write_cart_queries(rec_vec_t & records, std::filesystem::path const & cart_queries_path)
{
    using fields = seqan3::fields<seqan3::field::id, seqan3::field::seq>;
    using types = seqan3::type_list<std::string, std::vector<seqan3::dna4>>;
    using sequence_record_type = seqan3::sequence_record<types, fields>;

    seqan3::sequence_file_output fout{cart_queries_path, fields{}};

    for (auto & record : records)
    {
        sequence_record_type sequence_record{std::move(record.id()), std::move(record.sequence())};
        fout.push_back(sequence_record);
    }
}

} // namespace valik
