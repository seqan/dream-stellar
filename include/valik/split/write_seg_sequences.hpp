#pragma once

#include <valik/shared.hpp>
#include <valik/split/database_metadata.hpp>
#include <valik/split/database_segments.hpp>

namespace valik
{

/** !\brief Function that writes an output FASTA file for each segment sequence. */
void write_reference_segments(database_metadata const & reference_metadata,
                              database_segments & segments,
                              std::filesystem::path const & ref_path);

/** !\brief Function that writes segment sequences into a single FASTA file. */
void write_query_segments(database_metadata const & query_metadata,
                          database_segments & segments,
                          std::filesystem::path const & query_path);

}   // namespace valik
