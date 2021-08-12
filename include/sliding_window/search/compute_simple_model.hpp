#pragma once

#include <sliding_window/search/minimiser_model.hpp>
#include <sliding_window/shared.hpp>

namespace sliding_window
{

std::vector<size_t> compute_simple_model(search_arguments const & arguments);

} // namespace sliding_window
