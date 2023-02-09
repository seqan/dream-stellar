#pragma once

#include <string>

#include <seqan3/alphabet/nucleotide/dna4.hpp>

namespace valik
{

struct query_record
{
    std::string sequence_id;
    std::vector<seqan3::dna4> sequence;
};

} // namespace valik
