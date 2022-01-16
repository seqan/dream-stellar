#include <sliding_window/search/search_setup.hpp>

namespace sliding_window::app
{

//-----------------------------
//
// Setup IBF and launch multithreaded search.
//
//-----------------------------
template <bool compressed>
void run_program(search_arguments const &arguments, search_time_statistics & time_statistics)
{
    constexpr seqan3::data_layout ibf_data_layout = compressed ? seqan3::data_layout::compressed : seqan3::data_layout::uncompressed;
    using ibf_t = seqan3::interleaved_bloom_filter<ibf_data_layout>;
    ibf_t ibf{};

    auto cereal_worker = [&]()
    {
        auto start = std::chrono::high_resolution_clock::now();
        load_ibf(ibf, arguments);
        auto end = std::chrono::high_resolution_clock::now();
        time_statistics.ibf_io_time += std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
    };

    auto cereal_handle = std::async(std::launch::async, cereal_worker);

    seqan3::sequence_file_input<dna4_traits, seqan3::fields<seqan3::field::id, seqan3::field::seq>> fin{arguments.query_file};
    using record_type = typename decltype(fin)::record_type;
    std::vector<record_type> records{};

    threshold const threshold_data = make_threshold_data(arguments);

    sync_out synced_out{arguments.out_file};

    for (auto &&chunked_records : fin | seqan3::views::chunk((1ULL << 20) * 10))
    {
        records.clear();
        auto start = std::chrono::high_resolution_clock::now();
        std::ranges::move(chunked_records, std::cpp20::back_inserter(records));
        auto end = std::chrono::high_resolution_clock::now();
        time_statistics.reads_io_time += std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

        cereal_handle.wait();

        // not allowed to pass template functions to other functions, 
        // BUT allowed to pass specific instances of template functions to other functions
        write_output_file_parallel(worker<ibf_t, std::vector<record_type>>, ibf, arguments, records, threshold_data, synced_out, time_statistics.compute_time);
    }
}

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

} // namespace sliding_window::app
