#pragma once

#include <filesystem>

#include <valik/split/sequence_metadata.hpp>

#include <utilities/consolidate/stellar_match.hpp>

namespace valik
{

std::vector<stellar_match> read_stellar_output(std::filesystem::path const & match_path,
                                                      sequence_metadata const & reference,
                                                      std::ios_base::openmode const mode = std::ios_base::in);

void write_stellar_output(std::filesystem::path const & out_path,
                         std::vector<stellar_match> const & matches,
                         bool append = false);

} // namespace valik
