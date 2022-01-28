#pragma once

#include <seqan3/std/filesystem>

#include <seqan3/search/dream_index/interleaved_bloom_filter.hpp>

namespace valik
{

template <seqan3::data_layout ibf_data_layout>
void load_ibf(seqan3::interleaved_bloom_filter<ibf_data_layout> & ibf, std::filesystem::path const & ibf_file)
{
    static uint8_t kmer_size{};
    static uint32_t window_size{};

    std::ifstream is{ibf_file, std::ios::binary};
    cereal::BinaryInputArchive iarchive{is};

    iarchive(kmer_size);
    iarchive(window_size);
    iarchive(ibf);
}

} // namespace valik
