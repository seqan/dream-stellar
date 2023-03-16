#include <future>
#include <cstdlib>
#include <algorithm>

#include <valik/search/load_index.hpp>
#include <valik/search/query_record.hpp>
#include <valik/search/search_time_statistics.hpp>
#include <valik/search/write_output_file_parallel.hpp>
#include <valik/split/reference_segments.hpp>
#include <utilities/external_process.hpp>

#include <raptor/threshold/threshold.hpp>

#include <seqan3/io/sequence_file/output.hpp>


namespace valik::app
{

/* Creates a temporary folder in the temporary path of the OS
 *
 * \param name: a name with 'XXXXXX' at the end, e.g.: valik/call_XXXXXX
 * \return returns the name with the 'XXXXXX' replaced and the directory created
 *
 * throws if any errors occures
 */
static std::filesystem::path create_temporary_path(std::filesystem::path name) {
    if (!name.is_relative()) {
        throw std::runtime_error("Must be given a relative file");
    }
    auto path = std::filesystem::temp_directory_path() / name;
    auto path_str = path.native();
    create_directories(path.parent_path());
    auto str = std::vector<char>(path_str.size()+1, '\0'); // Must include an extra character to include a 0
    std::copy_n(path_str.data(), path_str.size(), str.data());
    auto ptr = mkdtemp(str.data());
    if (!ptr) {
        throw std::runtime_error("Could not create temporary folder: " + path_str);
    }
    return str.data();
}

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

    {
        auto start = std::chrono::high_resolution_clock::now();
        load_index(index, arguments.index_file);
        auto end = std::chrono::high_resolution_clock::now();
        time_statistics.index_io_time += std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
    }

    using fields = seqan3::fields<seqan3::field::id, seqan3::field::seq>;
    using types = seqan3::type_list<std::string, std::vector<seqan3::dna4>>;
    using sequence_record_type = seqan3::sequence_record<types, fields>;

    seqan3::sequence_file_input<dna4_traits, fields> fin{arguments.query_file};
    std::vector<query_record> query_records{};

    raptor::threshold::threshold const thresholder{arguments.make_threshold_parameters()};

    // the location of bin-query fasta files can be overwritten with an environment variable
    // the $VALIK_TMP directory has to exist and write permission must be granted
    std::filesystem::path tmp_path;
    if (auto ptr = std::getenv("VALIK_TMP"); ptr != nullptr)
        tmp_path = std::string(ptr);
    else
        tmp_path = create_temporary_path("valik/stellar_call_XXXXXX");

    std::string stellar_exec = "stellar";
    if (auto ptr = std::getenv("VALIK_STELLAR"); ptr != nullptr)
        stellar_exec = std::string(ptr);

    sync_out synced_out{arguments.out_file};
    auto queue = cart_queue<query_record>{index.ibf().bin_count(), arguments.cart_max_capacity, arguments.max_queued_carts};

    std::optional<reference_segments> segments;
    if (!arguments.seg_path.empty())
        segments = reference_segments(arguments.seg_path);

    //!WORKAROUND: Stellar does not allow smaller error rates
    double er_rate = std::max((double) arguments.errors / (double) arguments.pattern_size, 0.00001);

    std::ofstream text_out(arguments.out_file.string() + ".out");


    std::mutex mutex;
    std::unordered_map<size_t, size_t> bin_count;
    std::vector<std::string> output_files;

    auto consumerThreads = std::vector<std::jthread>{};
    for (size_t i = 0; i < arguments.threads; ++i)
    {
        consumerThreads.emplace_back(
        [&]() {
            for (auto next = queue.dequeue(); next; next = queue.dequeue())
            {
                auto & [bin_id, records] = *next;

                std::unique_lock g(mutex);
                std::filesystem::path path = tmp_path / std::string("query_" + std::to_string(bin_id) + "_" + std::to_string(bin_count[bin_id]++) + ".fasta");
                output_files.push_back(path.string() + ".gff");
                g.unlock();

                {
                    seqan3::sequence_file_output fout{path, fields{}};

                    for (auto & record : records)
                    {
                        sequence_record_type sequence_record{std::move(record.sequence_id), std::move(record.sequence)};
                        fout.push_back(sequence_record);
                    }
                }

                std::vector<std::string> process_args{stellar_exec};
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
                                                        "-o", std::string(path) + ".gff"});

                external_process process(process_args);

                text_out << process.cout();
                text_out << process.cerr();
            }

        });
    }

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
    consumerThreads.clear();

    std::vector<std::string> merge_process_args{"cat"};
    for (auto & path : output_files)
        merge_process_args.push_back(path);
    external_process merge(merge_process_args);

    std::ofstream matches_out(arguments.out_file);
    matches_out << merge.cout();
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
