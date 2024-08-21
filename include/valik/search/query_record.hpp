#pragma once

#include <string>
#include <vector>
#include <sstream>

#include <valik/split/metadata.hpp>
#include <dream_stellar/stellar_query_segment.hpp>

#include <seqan3/alphabet/nucleotide/dna4.hpp>
#include <seqan/sequence.h>

namespace valik
{

/**
 * @brief Each record owns the underlying data.
 *
 */
struct query_record
{
    std::string sequence_id;
    std::vector<seqan3::dna4> sequence;
};

/**
 * @brief Query sequence resources are shared between records.
 *
 */
template <typename seq_t>
struct shared_query_record
{
    std::string sequence_id;
    seq_t sequence;
    std::shared_ptr<seq_t> underlyingData;
    
    private:
        uint64_t start{0};
        uint64_t len;

    public:
        shared_query_record(std::string id, std::shared_ptr<seq_t> query_ptr) : 
                            sequence_id(std::move(id)), underlyingData(query_ptr)
        {
            sequence = seq_t((*query_ptr).begin(), (*query_ptr).end());
            len = (*query_ptr).size();
        }

        shared_query_record(std::string id, metadata::segment_stats const & seg, std::shared_ptr<seq_t> query_ptr) : 
                            sequence_id(std::move(id)), underlyingData(query_ptr), start(seg.start), len(seg.len)
        {
            sequence = seq_t((*query_ptr).begin() + seg.start, (*query_ptr).begin() + seg.start + seg.len);
        }

        shared_query_record(std::string id, uint64_t const other_start, uint64_t const other_len, std::shared_ptr<seq_t> query_ptr) : 
                            sequence_id(std::move(id)), underlyingData(query_ptr), start(other_start), len(other_len)
        {
            if ((*query_ptr).size() < (start + len))
                throw std::runtime_error("Incorrect segment definition. Out of range.");
                
            sequence = seq_t((*query_ptr).begin() + start, len);
        }

        dream_stellar::StellarQuerySegment<seq_t> get_seqan_segment() const
        {
            return {*(underlyingData), start, start + len};
        }

        uint64_t get_start() const
        {
            return start;
        }

        uint64_t get_len() const
        {
            return len;
        }
};

} // namespace valik
