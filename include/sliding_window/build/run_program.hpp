#pragma once

#include <sliding_window/build/ibf_factory.hpp>
#include <sliding_window/build/store_index.hpp>

namespace sliding_window
{

// TODO: refactor
// For split and search subroutines run_program is placed in sliding_window::app files  
template <bool compressed>
void run_program(build_arguments const & arguments)
{
    ibf_factory<compressed> generator{arguments};
    auto ibf = generator();
    store_index(arguments.out_path, ibf, arguments);
}

} // namespace sliding_window
