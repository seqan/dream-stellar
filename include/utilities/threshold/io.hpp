#pragma once

#include <utilities/threshold/shared.hpp>
#include <utilities/threshold/kmer_attributes.hpp>

namespace valik
{

/**
 * @brief Precalculate and write out FN configuration count tables.
*/
void write_precalc_fn_confs(std::filesystem::path const & outfile);

/**
 * @brief Deserialize kmer_attributes for a single k-mer size.
*/
kmer_attributes deserialize_kmer_attributes(std::string const & kmer_attr_str);

/**
 * @brief Read precalculated FN error configuration count tables across all k-mer sizes. 
*/
std::vector<kmer_attributes> read_fn_confs(std::filesystem::path const & infile);

}   // namespace valik
