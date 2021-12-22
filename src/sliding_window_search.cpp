#include <sliding_window/search/search_setup.hpp>

namespace sliding_window
{

void sliding_window_search(search_arguments const & arguments)
{
    search_time_statistics time_statistics{};

    if (arguments.compressed)
        run_program<true>(arguments, time_statistics);
    else
        run_program<false>(arguments, time_statistics);

    if (arguments.write_time)
        write_time_statistics(time_statistics, arguments);

    return;
}

} // namespace sliding_window
