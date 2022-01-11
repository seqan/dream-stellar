#pragma once

#include <robin_hood.h>

#include <seqan3/search/dream_index/interleaved_bloom_filter.hpp>
#include <seqan3/search/views/minimiser_hash.hpp>

#include <sliding_window/build/call_parallel_on_bins.hpp>

namespace sliding_window
{

bool check_for_fasta_format(std::vector<std::string> const & valid_extensions, std::string const & file_path);

void compute_minimiser(build_arguments const & arguments);

} // namespace sliding_window
