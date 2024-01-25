#pragma once

#include <utilities/threshold/kmer_attributes.hpp>

namespace valik
{

std::filesystem::path fn_filename();

/**
 * @brief Precalculate and write out FN configuration count tables.
*/
void precalc_fn_confs(std::vector<kmer_attributes> & attr_vec);

/**
 * @brief Read precalculated FN error configuration count tables across all k-mer sizes. 
*/
bool read_fn_confs(std::vector<kmer_attributes> & attr_vec);

}   // namespace valik
