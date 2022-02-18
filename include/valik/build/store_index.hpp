#pragma once

#include <valik/index.hpp>

namespace valik
{

template <typename data_t>
static inline void store_index(std::filesystem::path const & path,
                               valik_index<data_t> const & index)
{
    std::ofstream os{path, std::ios::binary};
    cereal::BinaryOutputArchive oarchive{os};
    oarchive(index);
}

} // namespace valik

