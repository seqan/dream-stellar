#include <sliding_window/search/run_program_single.hpp>
#include <sliding_window/search/run_program_multiple.hpp>

namespace sliding_window
{

void sliding_window_search(search_arguments const & arguments)
{
    if (arguments.parts == 1)
    {
        if (arguments.compressed)
            run_program_single<true>(arguments);
        else
            run_program_single<false>(arguments);
    }
    else
    {
        if (arguments.compressed)
            run_program_multiple<true>(arguments);
        else
            run_program_multiple<false>(arguments);
    }
    return;
}

} // namespace sliding_window
