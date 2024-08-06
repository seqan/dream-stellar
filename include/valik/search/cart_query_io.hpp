#pragma once

#include <filesystem>

#include <utilities/alphabet_wrapper/seqan/alphabet.hpp>
#include <valik/search/query_record.hpp>

#include <stellar/stellar_query_segment.hpp>
#include <stellar/io/import_sequence.hpp>

#include <seqan3/io/sequence_file/output.hpp>
#include <seqan3/io/sequence_file/record.hpp>
#include <seqan3/core/debug_stream.hpp>

namespace valik
{

/**
 *  \brief Function that creates a seqan2::Segment from a query_record (split or short query)
 *
 *  \param records vector containing valik split query segments
 *  \param seqs set of query segments (in-out)
 *  \param ids set of query segment ids (in-out)
 *  \param strOut stream for standard output
 *  \param strErr stream for error output
 *  \param hostQueries underlying sequences for query segments
 *  \param hostQueryIDs set of underlying sequence ids
 */
template <typename rec_vec_t, typename TStream, typename seq_vec_t>
inline bool get_cart_queries(rec_vec_t const & records,
                             seq_vec_t & seqs,
                             std::vector<std::string> & ids, 
                             TStream & strOut,
                             TStream & strErr)
{

    std::set<std::string> uniqueIds; // set of short IDs (cut at first whitespace)
    bool idsUnique = true;

    size_t seqCount{0};

    for (auto & record : records)
    {
        seqs.emplace_back(record.sequence);
        ids.emplace_back(record.sequence_id);
        seqCount++;
        idsUnique &= stellar::_checkUniqueId(uniqueIds, record.sequence_id);
    }

    strOut << "Loaded " << seqCount << " query sequence" << ((seqCount > 1) ? "s " : " ") << "from cart." << std::endl;
    if (!idsUnique)
        strErr << "WARNING: Non-unique query ids. Output can be ambiguous.\n";
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
        sequence_record_type sequence_record{std::move(record.sequence_id), std::move(record.sequence)};
        fout.push_back(sequence_record);
    }
}

} // namespace valik
