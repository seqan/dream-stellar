#include <valik/search/search.hpp>

namespace valik::app
{

/**
 * @brief Function that loads the index and launches local or distributed search.
 *
 * @param arguments Command line arguments.
 */
void valik_search(search_arguments const & arguments)
{
    search_time_statistics time_statistics{};

    //!TODO: this switch doesn't work, make is_compressed template parameter
    using index_structure_t = index_structure::ibf;
    if (arguments.compressed)
        using index_structure_t = index_structure::ibf_compressed;
    auto index = valik_index<index_structure_t>{};

    {
        auto start = std::chrono::high_resolution_clock::now();
        load_index(index, arguments.index_file);
        auto end = std::chrono::high_resolution_clock::now();
        time_statistics.index_io_time += std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
    }

    bool failed;
    if (arguments.distribute)
        failed = search_distributed(arguments, time_statistics, index);
    else
    {
        if (arguments.query_seg_path.empty())
            failed = search_local<false>(arguments, time_statistics, index);
        else
            failed = search_local<true>(arguments, time_statistics, index);
    }

    if (arguments.write_time)
        write_time_statistics(time_statistics, arguments.out_file.string() + ".time");

    if (failed) {
        throw std::runtime_error("valik_search failed. Run didn't complete correctly.");
    }
}

} // namespace valik::app
