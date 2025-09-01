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

    size_t size() const
    {
        return sequence.size();
    }
};

/**
 * @brief Query sequence resources are shared between records.
 *
 */
template <typename TSequence>
struct shared_query_record
{
    std::string sequence_id;
    seqan2::Segment<TSequence const, seqan2::InfixSegment> querySegment;
    std::shared_ptr<TSequence> underlyingData;

    shared_query_record(TSequence && seq, std::string && id) : sequence_id(std::move(id))
    {
        // make_shared returns a newly allocated object
        underlyingData = std::make_shared<TSequence>(std::move(seq));
        querySegment = seqan2::infix(*underlyingData, 0, seqan2::length(*underlyingData));
    }

    shared_query_record(std::string const & id, metadata::segment_stats const & seg, std::shared_ptr<TSequence> const & query_ptr) : sequence_id(id)
    {
        seqan2::Segment<TSequence const, seqan2::InfixSegment> inf = seqan2::infixWithLength(*query_ptr, seg.start, seg.len);
        querySegment = inf;
        underlyingData = query_ptr;
    }

    size_t size() const
    {
        return seqan2::length(querySegment);
    }
};

} // namespace valik
