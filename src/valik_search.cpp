#include <valik/search/load_index.hpp>
#include <valik/search/query_record.hpp>
#include <valik/search/search_time_statistics.hpp>
#include <valik/search/write_output_file_parallel.hpp>
#include <valik/split/reference_segments.hpp>

#include <utilities/external_process.hpp>

#include <raptor/threshold/threshold.hpp>

#include <seqan3/io/sequence_file/output.hpp>

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

    using fields = seqan3::fields<seqan3::field::id, seqan3::field::seq>;
    using types = seqan3::type_list<std::string, std::vector<seqan3::dna4>>;
    using sequence_record_type = seqan3::sequence_record<types, fields>;

    seqan3::sequence_file_input<dna4_traits, fields> fin{arguments.query_file};
    std::vector<query_record> query_records{};

    raptor::threshold::threshold const thresholder{arguments.make_threshold_parameters()};

    std::filesystem::path tmp_path{std::filesystem::temp_directory_path() / "valik"};
    //!TODO: this could require some error handling
    std::filesystem::create_directories(tmp_path);

    sync_out synced_out{arguments.out_file};
    cereal_handle.wait(); // We need the index to be loaded

    auto queue = cart_queue<query_record>{index.ibf().bin_count(), arguments.cart_max_capacity, arguments.max_queued_carts};


    std::optional<reference_segments> segments;
    if (!arguments.seg_path.empty())
        segments = reference_segments(arguments.seg_path);

    double er_rate = (double) arguments.errors / (double) arguments.pattern_size;

    auto consumerThread = std::jthread{[&]() {
        std::string result_string;

        size_t count = 0;
        for (auto next = queue.dequeue(); next; next = queue.dequeue())
        {
            auto & [bin_id, records] = *next;
            std::filesystem::path path = tmp_path / std::string("query_" + std::to_string(bin_id) + "_" + std::to_string(count) + ".fasta");
            {
                seqan3::sequence_file_output fout{path, fields{}};

                count++;
                for (auto & record : records)
                {
                    sequence_record_type sequence_record{std::move(record.sequence_id), std::move(record.sequence)};
                    fout.push_back(sequence_record);
                }
            }

            std::vector<std::string> process_args{"echo", "stellar"};
            if (segments)
            {
                auto seg = segments->segment_from_bin(bin_id);
                process_args.insert(process_args.end(), {index.bin_path()[0][0], std::string(path),
                                                        "--sequenceOfInterest", std::to_string(seg.ref_ind),
                                                        "--segmentBegin", std::to_string(seg.start),
                                                        "--segmentEnd", std::to_string(seg.start + seg.len)});
            }
            else
            {
                process_args.insert(process_args.end(), {index.bin_path()[bin_id][0], std::string(path)});
            }

            process_args.insert(process_args.end(), {"-e", std::to_string(er_rate),
                                                    "-l", std::to_string(arguments.pattern_size),
                                                    "-a", "dna",
                                                    "-o", std::string(path) + ".gff"});

            external_process process(process_args);

            std::cout << process.cout() << '\n';
            std::cout << process.cerr() << '\n';

    if (arguments.call_stellar)
    {

        /* call stellar on bin 2

        */
    }


        }

    }};


    for (auto &&chunked_records : fin | seqan3::views::chunk((1ULL << 20) * 10))
    {
        query_records.clear();
        auto start = std::chrono::high_resolution_clock::now();
        for (auto && query_record: chunked_records)
            query_records.emplace_back(std::move(query_record.id()), std::move(query_record.sequence()));

        auto end = std::chrono::high_resolution_clock::now();
        time_statistics.reads_io_time += std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

        start = std::chrono::high_resolution_clock::now();

        //TODO: pass index and overlap instead of ibf and all parameters
        write_output_file_parallel(index.ibf(), arguments, query_records, thresholder, queue);
        end = std::chrono::high_resolution_clock::now();
        time_statistics.compute_time += std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
    }
    queue.finish(); // Flush carts that are not empty yet
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
