#pragma once

#include <string>
#include <vector>
#include <sstream>

#include <valik/split/metadata.hpp>

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

    shared_query_record(std::string id, std::shared_ptr<seq_t> query_ptr) : 
                        sequence_id(std::move(id)), underlyingData(query_ptr)
    {
        sequence = seq_t((*query_ptr).begin(), (*query_ptr).end());
    }

    shared_query_record(std::string id, metadata::segment_stats const & seg, std::shared_ptr<seq_t> query_ptr) : 
                        sequence_id(std::move(id)), underlyingData(query_ptr)
    {
        sequence = seq_t((*query_ptr).begin() + seg.start, (*query_ptr).begin() + seg.start + seg.len);
    }
};

} // namespace valik
