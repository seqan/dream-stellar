#include <sliding_window/build/build.hpp>
#include <sliding_window/build/run_program.hpp>

namespace sliding_window::app
{

void sliding_window_build(build_arguments const & arguments)
{
    if (arguments.compressed)
        run_program<true>(arguments);
    else
        run_program<false>(arguments);
    return;
}

} // namespace sliding_window::app
