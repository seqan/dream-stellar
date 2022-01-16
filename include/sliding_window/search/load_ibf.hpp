#pragma once

#include <chrono>
#include <seqan3/std/filesystem>

#include <sliding_window/shared.hpp>

namespace sliding_window
{

template <typename t>
void load_ibf(t & ibf, search_arguments const & arguments)
{
    static uint8_t kmer_size{};
    static uint32_t window_size{};

    std::ifstream is{arguments.ibf_file, std::ios::binary};
    cereal::BinaryInputArchive iarchive{is};

    iarchive(kmer_size);
    iarchive(window_size);
    iarchive(ibf);
}

} // namespace sliding_window
