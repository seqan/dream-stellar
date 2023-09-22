#pragma once

#include <valik/shared.hpp>
#include <valik/split/metadata.hpp>

namespace valik
{

/** !\brief Function that writes an output FASTA file for each segment sequence. */
void write_reference_segments(metadata & reference_metadata,
                              std::filesystem::path const & ref_path);

/** !\brief Function that writes segment sequences into a single FASTA file. */
void write_query_segments(metadata & query_metadata,
                          std::filesystem::path const & query_path);

}   // namespace valik
