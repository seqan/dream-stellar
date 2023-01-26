#include <valik/search/load_index.hpp>
#include <valik/search/query_record.hpp>
#include <valik/search/search_time_statistics.hpp>
#include <valik/search/write_output_file_parallel.hpp>

#include <valik/split/reference_segments.hpp>

#include <raptor/threshold/threshold.hpp>

#include <future>

namespace valik::app
{

//-----------------------------
//
// Setup IBF and launch multithreaded search.
//
//-----------------------------
template <bool compressed>
void run_program(search_arguments const &arguments, search_time_statistics & time_statistics)
{
    using index_structure_t = std::conditional_t<compressed, index_structure::ibf_compressed, index_structure::ibf>;
    auto index = valik_index<index_structure_t>{};

    auto cereal_worker = [&]()
    {
        auto start = std::chrono::high_resolution_clock::now();
        load_index(index, arguments.index_file);
        auto end = std::chrono::high_resolution_clock::now();
        time_statistics.index_io_time += std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
    };

    auto cereal_handle = std::async(std::launch::async, cereal_worker);

    seqan3::sequence_file_input<dna4_traits, seqan3::fields<seqan3::field::id, seqan3::field::seq>> fin{arguments.query_file};
    std::vector<query_record> query_records{};

    raptor::threshold::threshold const thresholder{arguments.make_threshold_parameters()};

    if (arguments.call_stellar)
    {
        reference_segments segments(arguments.seg_path);

        /* call stellar on bin 2
        double er_rate = (double) arguments.errors / (double) arguments.pattern_size;
        auto seg = segments.segment_from_bin(2);
        stellar index.bin_path()[0][0]
                query.fasta
                --sequenceOfInterest seg.ref_ind;
                --segmentBegin seg.start;
                --segmentEnd seg.start + seg.length;
                -e er_rate
                -l arguments.pattern_size
                -a dna
                -o out.gff
        */
    }

    sync_out synced_out{arguments.out_file};

    size_t record_id = 0u;
    for (auto &&chunked_records : fin | seqan3::views::chunk((1ULL << 20) * 10))
    {
        query_records.clear();
        auto start = std::chrono::high_resolution_clock::now();
        for (auto && query_record: chunked_records)
        {
            query_records.emplace_back(record_id, std::move(query_record.id()), std::move(query_record.sequence()));
            ++record_id;
        }
        auto end = std::chrono::high_resolution_clock::now();
        time_statistics.reads_io_time += std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

        cereal_handle.wait();

        start = std::chrono::high_resolution_clock::now();

        //TODO: pass index and overlap instead of ibf and all parameters
        write_output_file_parallel(index.ibf(), arguments, query_records, thresholder, synced_out);
        end = std::chrono::high_resolution_clock::now();
        time_statistics.compute_time += std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
    }
}

void valik_search(search_arguments const & arguments)
{
    search_time_statistics time_statistics{};

    if (arguments.compressed)
        run_program<seqan3::data_layout::compressed>(arguments, time_statistics);
    else
        run_program<seqan3::data_layout::uncompressed>(arguments, time_statistics);

    if (arguments.write_time)
        write_time_statistics(time_statistics, arguments);

    return;
}

} // namespace valik::app
