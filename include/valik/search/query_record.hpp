#pragma once

#include <string>

#include <seqan3/alphabet/nucleotide/dna4.hpp>

namespace valik
{

struct query_record
{
// workaround for gcc 9.x; for some reasons std::vector<query_record>::emplace_back() can't be used
// if this constructor is missing
#if defined(__GNUC__) && __GNUC__ <= 9
    query_record() = default;
    query_record(size_t record_id, std::string sequence_id, std::vector<seqan3::dna4> sequence)
        : record_id{record_id}, sequence_id{std::move(sequence_id)}, sequence{std::move(sequence)}
    {}
#endif // defined(__GNUC__) && __GNUC__ <= 9

    size_t record_id;
    std::string sequence_id;
    std::vector<seqan3::dna4> sequence;
};

} // namespace valik
