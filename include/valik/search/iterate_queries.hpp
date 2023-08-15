#pragma once

#include <valik/search/prefilter_queries_parallel.hpp>
#include <valik/search/search_time_statistics.hpp>
#include <valik/split/database_segments.hpp>

namespace valik::app
{

/**
 * @brief Function that sends chunks of queries to the prefilter which then writes shopping carts onto disk.
 *
 * @param arguments Command line arguments.
 * @param time_statistics Run-time statistics.
 * @param ibf Interleaved Bloom Filter.
 * @param queue Shopping cart queue for load balancing between prefiltering and Stellar search.
 */
template <typename ibf_t, typename cart_queue_t>
void iterate_distributed_queries(search_arguments const & arguments,
                                 search_time_statistics & time_statistics, // IN-OUT parameter
                                 ibf_t const & ibf,
                                 cart_queue_t & queue)
{
    using fields = seqan3::fields<seqan3::field::id, seqan3::field::seq>;
    std::vector<query_record> query_records{};
    raptor::threshold::threshold const thresholder{arguments.make_threshold_parameters()};
    seqan3::sequence_file_input<dna4_traits, fields> fin{arguments.query_file};
    for (auto &&chunked_records : fin | seqan3::views::chunk((1ULL << 20) * 10))
    {
        query_records.clear();
        auto start = std::chrono::high_resolution_clock::now();
        for (auto && fasta_record: chunked_records)
            query_records.emplace_back(std::move(fasta_record.id()), std::move(fasta_record.sequence()));

        auto end = std::chrono::high_resolution_clock::now();
        time_statistics.reads_io_time += std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        prefilter_queries_parallel(ibf, arguments, query_records, thresholder, queue);
        end = std::chrono::high_resolution_clock::now();
        time_statistics.prefilter_time += std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
    }
}

//!WORKAROUND: partial specialization of template functions is not allowed
// primary template
template <typename cart_queue_t, typename ibf_t>
struct iteration_wrapper
{
    static void go(seqan2::StringSet<seqan2::String<seqan2::Dna>> const & hostQueries,
                   seqan2::StringSet<seqan2::CharString> const & hostQueryIDs,
                   search_arguments const & arguments,
                   search_time_statistics & time_statistics, // IN-OUT parameter
                   ibf_t const & ibf,
                   cart_queue_t & queue,
                   database_segments & segments)
    {
        return;
    }
};


/**
 * @brief Class that sends query segments to the prefilter which then inserts them to the shopping cart queue.
 *        Partial template specialization (split queries).
 * @param arguments Command line arguments.
 * @param time_statistics Run-time statistics.
 * @param ibf Interleaved Bloom Filter.
 * @param queue Shopping cart queue for load balancing between prefiltering and Stellar search.
 */
/*
template <typename ibf_t>
struct iteration_wrapper<cart_queue<split_query_record<seqan2::String<seqan2::Dna>>>, ibf_t>
{
    static void go(seqan2::StringSet<seqan2::Segment<seqan2::String<seqan2::Dna> const, seqan2::InfixSegment>> & hostQueries,
                   seqan2::StringSet<seqan2::CharString> const & hostQueryIDs,
                   search_arguments const & arguments,
                   search_time_statistics & time_statistics, // IN-OUT parameter
                   ibf_t const & ibf,
                   cart_queue<split_query_record<seqan2::String<seqan2::Dna>>> & queue,
                   database_segments & segments)
    {
        using namespace seqan3::literals;
        using TSequence = seqan2::String<seqan2::Dna>;
        std::vector<split_query_record<TSequence>> query_records{};
        raptor::threshold::threshold const thresholder{arguments.make_threshold_parameters()};

        size_t id{0};
        for (auto const & query : hostQueries)
        {
            query_records.clear();
            auto start = std::chrono::high_resolution_clock::now();
            auto segments_from_id = [&](database_segments::segment & seg) {return id == seg.seq_ind;};
            for (auto const & seg : segments.members | std::views::filter(segments_from_id))
            {
                // convert the seqan2::String<Dna> to a std::vector<seqan3::dna4>
                //!TODO: can this copy be avoided?
                seqan2::Segment<TSequence const, seqan2::InfixSegment> inf = seqan2::infixWithLength(query, seg.start, seg.len);

                std::stringstream seq_str_stream;
                for (int i = 0; i < seg.len; i++)
                    seq_str_stream << inf[i];

                //!TODO: populate seg_vec
                std::vector<seqan3::dna4> seg_vec{};

                // convert the seqan2::String<char> ID to a std::string ID
                std::stringstream id_str_stream;
                for (auto it = begin(hostQueryIDs[id]); it != end(hostQueryIDs[id]); ++it)
                    id_str_stream << *it;

                query_records.emplace_back(id_str_stream.str(), seg.start, std::move(seg_vec), &query);
            }
            auto end = std::chrono::high_resolution_clock::now();
            time_statistics.reads_io_time += std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

            start = std::chrono::high_resolution_clock::now();
            prefilter_queries_parallel<split_query_record<seqan2::String<seqan2::Dna>>>(ibf, arguments, query_records, thresholder, queue);
            end = std::chrono::high_resolution_clock::now();
            time_statistics.prefilter_time += std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

            id++;
        }
    }
};
*/


/**
 * @brief Class that sends chunks of queries to the prefilter which then inserts them to the shopping cart queue.
 *        Partial template specialization (short queries).
 *
 * @param arguments Command line arguments.
 * @param time_statistics Run-time statistics.
 * @param ibf Interleaved Bloom Filter.
 * @param queue Shopping cart queue for load balancing between prefiltering and Stellar search.
 */
template <typename ibf_t>
void read_short_queries(seqan2::StringSet<seqan2::String<seqan2::Dna>> const & underlyingQueries,
                seqan2::StringSet<seqan2::CharString> const & underlyingQueryIDs,
                std::vector<seqan2::Segment<seqan2::String<seqan2::Dna> const, seqan2::InfixSegment>> & hostQueries,
                search_arguments const & arguments,
                search_time_statistics & time_statistics, // IN-OUT parameter
                ibf_t const & ibf,
                cart_queue<short_query_record<seqan2::String<seqan2::Dna>>> & queue)
{
    using TSequence = seqan2::String<seqan2::Dna>;
    using fields = seqan3::fields<seqan3::field::id, seqan3::field::seq>;
    std::vector<short_query_record<TSequence>> query_records{};
    raptor::threshold::threshold const thresholder{arguments.make_threshold_parameters()};

    /*
    seqan2::SeqFileIn inSeqs;
    if (!open(inSeqs, arguments.query_file.c_str()))
    {
        std::cerr << "Failed to open query file." << std::endl;
    }

    std::set<std::string> uniqueIds; // set of short IDs (cut at first whitespace)
    bool idsUnique = true;

    seqan2::String<seqan2::Dna> queryStr;
    std::string fastaID;
    uint32_t seqCount{0};
    std::cout << "\niterate_queries\n";
    for (; !seqan2::atEnd(inSeqs); ++seqCount)
    {
        auto start = std::chrono::high_resolution_clock::now();
        seqan2::readRecord(fastaID, queryStr, inSeqs);

        idsUnique &= stellar::_checkUniqueId(uniqueIds, fastaID);
        seqan2::appendValue(underlyingQueries, queryStr, seqan2::Generous());
        std::cout << std::addressof(underlyingQueries[seqan2::length(underlyingQueries) - 1]) <<
             '\t' << underlyingQueries[seqan2::length(underlyingQueries) - 1] << '\n';

        seqan2::appendValue(underlyingQueryIDs, fastaID, seqan2::Generous());
        seqCount++;
        auto end = std::chrono::high_resolution_clock::now();
        time_statistics.reads_io_time += std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
    }
    */


    for (size_t i{0}; i < seqan2::length(underlyingQueries); i++)
    {
        std::vector<seqan3::dna4> seg_vec{};
        for (auto & c : underlyingQueries[i])
        {
            seqan3::dna4 nuc;
            nuc.assign_char(c);
            seg_vec.push_back(nuc);
        }

        query_records.emplace_back(seqan2::toCString(underlyingQueryIDs[i]), std::move(seg_vec),
                                   seqan2::infix(underlyingQueries[i], 0, seqan2::length(underlyingQueries[i])));
    }

    auto start = std::chrono::high_resolution_clock::now();
    prefilter_queries_parallel<short_query_record<seqan2::String<seqan2::Dna>>>(ibf, arguments, query_records, thresholder, queue);
    auto end = std::chrono::high_resolution_clock::now();
    time_statistics.prefilter_time += std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
}

template <typename ibf_t>
void read_split_queries(seqan2::StringSet<seqan2::String<seqan2::Dna>> const & underlyingQueries,
                seqan2::StringSet<seqan2::CharString> const & underlyingQueryIDs,
                std::vector<seqan2::Segment<seqan2::String<seqan2::Dna> const, seqan2::InfixSegment>> & hostQueries,
                search_arguments const & arguments,
                search_time_statistics & time_statistics, // IN-OUT parameter
                ibf_t const & ibf,
                cart_queue<short_query_record<seqan2::String<seqan2::Dna>>> & queue,
                database_segments & segments)
{
    using TSequence = seqan2::String<seqan2::Dna>;
    using fields = seqan3::fields<seqan3::field::id, seqan3::field::seq>;
    std::vector<short_query_record<TSequence>> query_records{};
    raptor::threshold::threshold const thresholder{arguments.make_threshold_parameters()};

    /*
    seqan2::SeqFileIn inSeqs;
    if (!open(inSeqs, arguments.query_file.c_str()))
    {
        std::cerr << "Failed to open query file." << std::endl;
    }

    std::set<std::string> uniqueIds; // set of short IDs (cut at first whitespace)
    bool idsUnique = true;

    seqan2::String<seqan2::Dna> queryStr;
    std::string fastaID;
    uint32_t seqCount{0};
    std::cout << "\niterate_queries\n";
    for (; !seqan2::atEnd(inSeqs); ++seqCount)
    {
        auto start = std::chrono::high_resolution_clock::now();
        seqan2::readRecord(fastaID, queryStr, inSeqs);

        idsUnique &= stellar::_checkUniqueId(uniqueIds, fastaID);
        seqan2::appendValue(underlyingQueries, queryStr, seqan2::Generous());
        std::cout << std::addressof(underlyingQueries[seqan2::length(underlyingQueries) - 1]) <<
             '\t' << underlyingQueries[seqan2::length(underlyingQueries) - 1] << '\n';

        seqan2::appendValue(underlyingQueryIDs, fastaID, seqan2::Generous());
        seqCount++;
        auto end = std::chrono::high_resolution_clock::now();
        time_statistics.reads_io_time += std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
    }
    */

    //std::cout << "iterate_queries" << '\n';
    size_t id{0};
    for (auto const & query : underlyingQueries)
    {
        auto segments_from_id = [&](database_segments::segment & seg) {return id == seg.seq_ind;};
        for (auto const & seg : segments.members | std::views::filter(segments_from_id))
        {
            seqan2::Segment<TSequence const, seqan2::InfixSegment> inf = seqan2::infixWithLength(query, seg.start, seg.len);

            std::vector<seqan3::dna4> seg_vec{};
            for (auto & c : inf)
            {
                seqan3::dna4 nuc;
                nuc.assign_char(c);
                seg_vec.push_back(nuc);
            }

            query_records.emplace_back(seqan2::toCString(underlyingQueryIDs[id]), std::move(seg_vec), inf);
            //std::cout << inf << '\n';
        }
        id++;
    }

    auto start = std::chrono::high_resolution_clock::now();
    prefilter_queries_parallel<short_query_record<seqan2::String<seqan2::Dna>>>(ibf, arguments, query_records, thresholder, queue);
    auto end = std::chrono::high_resolution_clock::now();
    time_statistics.prefilter_time += std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
}


/*

template <typename ibf_t>
struct iteration_wrapper<cart_queue<short_query_record<seqan2::String<seqan2::Dna>>>, ibf_t>
{

};

// function calling member function in wrapper class
template <typename cart_queue_t, typename ibf_t, typename querySet_t>
void iterate_queries(querySet_t & hostQueries,
                     seqan2::StringSet<seqan2::CharString> & hostQueryIDs,
                     search_arguments const & arguments,
                     search_time_statistics & time_statistics, // IN-OUT parameter
                     ibf_t const & ibf,
                     cart_queue_t & queue,
                     database_segments & segments)
{
    //auto wrapper = iteration_wrapper<cart_queue_t, ibf_t>();
    iteration_wrapper<cart_queue_t, ibf_t>::go(hostQueries, hostQueryIDs, arguments, time_statistics, ibf, queue, segments);
}

*/


}   // namespace valik::app
