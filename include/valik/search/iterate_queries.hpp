#pragma once

#include <valik/search/producer_threads_parallel.hpp>
#include <valik/search/search_time_statistics.hpp>
#include <valik/shared.hpp>

#include <dream_stellar/io/import_sequence.hpp>

#include <seqan/seq_io.h>

#include <seqan3/io/sequence_file/all.hpp>

namespace valik::app
{

/**
 * @brief Function that sends chunks of queries to the prefilter which then writes shopping carts onto disk.
 *
 * @param arguments Command line arguments.
 * @param ibf Interleaved Bloom Filter.
 * @param thresholder Threshold for number of shared k-mers.
 * @param queue Shopping cart queue for load balancing between prefiltering and Stellar search.
 */
template <typename ibf_t, typename cart_queue_t>
void iterate_distributed_queries(search_arguments const & arguments,
                                 ibf_t const & ibf,
                                 raptor::threshold::threshold const & thresholder,
                                 cart_queue_t & queue)
{
    using fields = seqan3::fields<seqan3::field::id, seqan3::field::seq>;
    std::vector<query_record<seqan3::dna4>> query_records{};
    seqan3::sequence_file_input<dna4_traits, fields> fin{arguments.query_file};
    for (auto &&chunked_records : fin | seqan3::views::chunk((1ULL << 20) * 10))
    {
        query_records.clear();
        for (auto && fasta_record: chunked_records)
            query_records.emplace_back(std::move(fasta_record.id()), std::move(fasta_record.sequence()));

        prefilter_queries_parallel(ibf, arguments, query_records, thresholder, queue);
    }
}

//!TODO: iterate queries remove duplicate code
/**
 * @brief Function that creates a query record from each query sequence and sends it to Stellar search.
 *
 * @param ref_seg_count Number of reference segments i.e the distribution granularity.
 * @param arguments Command line arguments.
 * @param queue Shopping cart queue for sending queries over to Stellar search.
 */
template <typename alphabet_t>
void iterate_all_queries(size_t const ref_seg_count,
                         search_arguments const & arguments,
                         cart_queue<shared_query_record<alphabet_t>> & queue)
{
    constexpr uint64_t chunk_size = (1ULL << 20) * 10;

    seqan3::sequence_file_input<dna4_adaptor_traits> fin{arguments.query_file};
    std::vector<query_record<alphabet_t>> query_records{};
    std::vector<shared_query_record<alphabet_t>> query_references{};

    std::set<std::string> unique_ids; // set of short IDs (cut at first whitespace)
    bool ids_unique{true};

    for (auto & record : fin)
    {
        query_records.emplace_back(std::move(record.id()), std::move(record.sequence()));
        auto & added_record = query_records[query_records.size() - 1]; 
        ids_unique &= dream_stellar::_checkUniqueId(unique_ids, added_record.id());
        query_references.emplace_back(added_record.id(), std::make_shared<std::vector<alphabet_t>>(added_record.sequence()));

        if (query_references.size() > chunk_size)
        {
            search_all_parallel<shared_query_record<alphabet_t>>(ref_seg_count, arguments, query_references, queue);
            query_references.clear();
            query_records.clear();
        }
    }

    if (!ids_unique)
        std::cerr << "WARNING: Non-unique query ids. Output can be ambiguous.\n";

    search_all_parallel<shared_query_record<alphabet_t>>(ref_seg_count, arguments, query_references, queue);    
}

/**
 * @brief Function that creates short query records from fasta file input and sends them for prefiltering.
 *
 * @tparam ibf_t Interleaved Bloom Filter type.
 * @param arguments Command line arguments.
 * @param ibf Interleaved Bloom Filter of the reference database.
 * @param thresholder Threshold for number of shared k-mers.
 * @param queue Shopping cart queue for load balancing between Valik prefiltering and Stellar search.
 */
template <typename ibf_t, typename alphabet_t>
void iterate_short_queries(search_arguments const & arguments,
                           ibf_t const & ibf,
                           raptor::threshold::threshold const & thresholder,
                           cart_queue<shared_query_record<alphabet_t>> & queue)
{
    constexpr uint64_t chunk_size = (1ULL << 20) * 10;

    seqan3::sequence_file_input<dna4_adaptor_traits> fin{arguments.query_file};
    //!TODO: reserve chunk size?
    std::vector<query_record<alphabet_t>> query_records{};
    std::vector<shared_query_record<alphabet_t>> query_references{};

    std::set<std::string> unique_ids; // set of short IDs (cut at first whitespace)
    bool ids_unique{true};

    for (auto & record : fin)
    {
        query_records.emplace_back(std::move(record.id()), std::move(record.sequence()));
        query_record<alphabet_t> & added_record = query_records[query_records.size() - 1];
        ids_unique &= dream_stellar::_checkUniqueId(unique_ids, added_record.id());
        query_references.emplace_back(added_record.id(), std::make_shared<std::vector<alphabet_t>>(added_record.sequence()));
        
        if (query_records.size() > chunk_size)
        {
            prefilter_queries_parallel<shared_query_record<alphabet_t>>(ibf, arguments, query_references, thresholder, queue);
            query_references.clear();
            query_records.clear();
        }
    }

    if (!ids_unique)
        std::cerr << "WARNING: Non-unique query ids. Output can be ambiguous.\n";

    prefilter_queries_parallel<shared_query_record<alphabet_t>>(ibf, arguments, query_references, thresholder, queue);
}

/**
 * @brief Function that creates split query records from fasta file input and sends them for prefiltering.
 *
 * @tparam ibf_t Interleaved Bloom Filter type.
 * @param arguments Command line arguments.
 * @param ibf Interleaved Bloom Filter of the reference database.
 * @param thresholder Threshold for number of shared k-mers.
 * @param queue Shopping cart queue for load balancing between Valik prefiltering and Stellar search.
 * @param meta Metadata table for split query segments.
 */
template <typename ibf_t, typename alphabet_t>
void iterate_split_queries(search_arguments const & arguments,
                           ibf_t const & ibf,
                           raptor::threshold::threshold const & thresholder,
                           cart_queue<shared_query_record<alphabet_t>> & queue,
                           metadata & meta)
{
    constexpr uint64_t chunk_size = (1ULL << 20) * 10;

    seqan3::sequence_file_input<dna4_adaptor_traits> fin{arguments.query_file};
    std::vector<query_record<alphabet_t>> query_records{};
    std::vector<shared_query_record<alphabet_t>> query_references{};

    std::set<std::string> unique_ids; // set of short IDs (cut at first whitespace)
    bool ids_unique{true};

    size_t seq_count{0};
    for (auto & record : fin)
    {
        ids_unique &= dream_stellar::_checkUniqueId(unique_ids, record.id());
        query_records.emplace_back(std::move(record.id()), std::move(record.sequence()));
        auto & added_record = query_records[query_records.size() - 1];
        auto query_ptr = std::make_shared<std::vector<alphabet_t>>(added_record.sequence());
        for (auto const & seg : meta.segments_from_ind(seq_count))
        {
            // each split query record contains a copy of the same shared pointer
            query_references.emplace_back(added_record.id(), seg.start, seg.len, query_ptr);

            if (query_records.size() > chunk_size)
            {
                prefilter_queries_parallel<shared_query_record<alphabet_t>>(ibf, arguments, query_references, thresholder, queue);
                query_references.clear();
                query_records.clear(); 
            }
        }
        seq_count++;
    }

    if (!ids_unique)
        std::cerr << "WARNING: Non-unique query ids. Output can be ambiguous.\n";

    prefilter_queries_parallel<shared_query_record<alphabet_t>>(ibf, arguments, query_references, thresholder, queue);
}

}   // namespace valik::app
