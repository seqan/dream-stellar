#include <sliding_window/build/build.hpp>
#include <sliding_window/build/build_from_minimiser.hpp>
#include <sliding_window/build/compute_minimiser.hpp>
#include <sliding_window/build/run_program.hpp>

namespace sliding_window::app
{

void sliding_window_build(build_arguments const & arguments)
{
    if (arguments.compute_minimiser)
    {
        compute_minimiser(arguments);
        return;
    }

    if (arguments.bin_path[0][0].extension() == ".minimiser")
    {
        if (arguments.compressed)
            build_from_minimiser<true>(arguments);
        else
            build_from_minimiser<false>(arguments);
        return;
    }

    if (arguments.compressed)
        run_program<true>(arguments);
    else
        run_program<false>(arguments);
    return;
}

} // namespace sliding_window::app
