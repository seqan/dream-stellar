#pragma once

#include <valik/shared.hpp>

#include <cmath>

namespace valik::detail
{

size_t next_power_of_two(size_t n);

size_t find_segment_length(size_t total_len, size_t min_len, size_t min_bins);

} // namespace valik::detail
