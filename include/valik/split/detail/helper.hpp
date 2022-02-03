#pragma once

#include <valik/shared.hpp>

#include <cmath>

namespace valik::detail
{

size_t next_power_of_two(size_t n);

void set_segment_arguments(size_t total_len, split_arguments & arguments);

} // namespace valik::detail
