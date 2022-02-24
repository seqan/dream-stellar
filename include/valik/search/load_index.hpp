#pragma once

#include <filesystem>

#include <valik/index.hpp>
#include <valik/shared.hpp>

namespace valik
{

template <typename index_t>
void load_index(index_t & index, std::filesystem::path const & index_file)
{
    std::ifstream is{index_file, std::ios::binary};
    cereal::BinaryInputArchive iarchive{is};

    iarchive(index);
}

} // namespace valik
