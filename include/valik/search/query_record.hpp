#pragma once

#include <string>
#include <vector>
#include <sstream>

//#include <valik/split/metadata.hpp>
#include <dream_stellar/stellar_query_segment.hpp>

#include <seqan3/alphabet/nucleotide/dna4.hpp>
#include <seqan/sequence.h>

namespace valik
{

/**
 * @brief Each record owns the underlying data.
 *
 */
template <typename alphabet_t = seqan3::dna4>
class query_record
{
    std::string sequence_id;
    std::vector<alphabet_t> query_sequence;

    public:
        query_record() = default;
        query_record(std::string const & id, std::vector<alphabet_t> const & seq) : sequence_id(id), query_sequence(seq) {}
        
        std::string id() const
        {
            return sequence_id;
        }

        std::vector<alphabet_t> sequence() const
        {
            return query_sequence;
        }
};

/**
 * @brief Query sequence resources are shared between records.
 *
 */
template <typename alphabet_t>
class shared_query_record
{
    using sequence_container_t = std::vector<alphabet_t>;
    using sequence_reference_t = std::span<const alphabet_t>;

    std::string sequence_id;
    sequence_reference_t query_sequence;
    std::shared_ptr<sequence_container_t> host_ptr;

    public:
        shared_query_record(std::string id, std::shared_ptr<sequence_container_t> query_ptr) : 
                            sequence_id(std::move(id)), host_ptr(query_ptr)
        {
            query_sequence = sequence_reference_t(*query_ptr);
        }

        /*
        shared_query_record(std::string id, metadata::segment_stats const & seg, std::shared_ptr<sequence_container_t> query_ptr) : 
                            sequence_id(std::move(id)), host_ptr(query_ptr)
        {
            if ((*query_ptr).size() < (seg.start + seg.len))
                throw std::runtime_error("Incorrect segment definition. Out of range.");

            sequence = sequence_reference_t((*query_ptr).begin() + seg.start, seg.len);
        }
        */

        shared_query_record(std::string id, uint64_t const other_start, uint64_t const other_len, 
                            std::shared_ptr<sequence_container_t> query_ptr) : 
                            sequence_id(id), host_ptr(query_ptr)
        {
            if ((*query_ptr).size() < (other_start + other_len))
                throw std::runtime_error("Incorrect segment definition. Out of range.");

            query_sequence = sequence_reference_t((*query_ptr).begin() + other_start /* begin */, other_len /* count */);
        }

        std::span<const alphabet_t> sequence() const
        {
            return query_sequence;
        }

        std::string id() const
        {
            return sequence_id;
        }

        std::span<const alphabet_t> host() const
        {
            return {*host_ptr};
        }

        uint64_t start() const
        {
            return (query_sequence.data() - (*host_ptr).data());
        }

        uint64_t len() const
        {
            return query_sequence.size();
        }

        dream_stellar::StellarQuerySegment<const alphabet_t> asStellarSegment() const
        {
            return {host(), start() /* begin */, start() + len() /* end */};
        }
};

} // namespace valik
