#include <seqan3/search/dream_index/interleaved_bloom_filter.hpp>
#include <seqan3/core/debug_stream.hpp>
#include <seqan3/utility/views/slice.hpp>   // provides views::slice

#include <sliding_window/search/compute_simple_model.hpp>
#include <sliding_window/search/do_parallel.hpp>
#include <sliding_window/search/load_ibf.hpp>
#include <sliding_window/search/query_result.hpp>
#include <sliding_window/search/sync_out.hpp>

#include <indexed_minimiser_hash.hpp>

namespace sliding_window
{

//-----------------------------
// 
// Precalculate vector with all pattern begin positions in read. 
// This adds a small computational overhead but makes the code much more readable.
//
//-----------------------------
std::vector<size_t> precalculate_begin(size_t const read_len, uint64_t const pattern_size, uint64_t const overlap)
{
    std::vector<size_t> begin_vector;
    for (size_t i = 0; i <= read_len - pattern_size;
    		i = i + pattern_size - overlap)
    {
        begin_vector.push_back(i);  
    }
    if (begin_vector.back() < read_len - pattern_size)
    {   
        // last pattern might have a smaller overlap to make sure the end of the read is covered
        begin_vector.push_back(read_len - pattern_size);
    }

    return begin_vector;
}

//-----------------------------
//
// Search reads in IBF. 
//
//-----------------------------
template <bool compressed>
void run_program_single(search_arguments const & arguments)
{
    constexpr seqan3::data_layout ibf_data_layout = compressed ? seqan3::data_layout::compressed :
                                                                 seqan3::data_layout::uncompressed;
    auto ibf = seqan3::interleaved_bloom_filter<ibf_data_layout>{};

    double ibf_io_time{0.0};
    double reads_io_time{0.0};
    double compute_time{0.0};

    auto cereal_worker = [&] ()
    {
        load_ibf(ibf, arguments, ibf_io_time);
    };
    auto cereal_handle = std::async(std::launch::async, cereal_worker);

    seqan3::sequence_file_input<dna4_traits, seqan3::fields<seqan3::field::id, seqan3::field::seq>> fin{arguments.query_file};
    using record_type = typename decltype(fin)::record_type;
    std::vector<record_type> records{};

    sync_out synced_out{arguments.out_file};

    size_t const kmers_per_window = arguments.window_size - arguments.kmer_size + 1;
    size_t const kmers_per_pattern = arguments.pattern_size - arguments.kmer_size + 1;
    size_t const min_number_of_minimisers = kmers_per_window == 1 ? kmers_per_pattern :
                                                std::ceil(kmers_per_pattern / static_cast<double>(kmers_per_window));
    size_t const kmer_lemma = arguments.pattern_size + 1u > (arguments.errors + 1u) * arguments.kmer_size ?
                                arguments.pattern_size + 1u - (arguments.errors + 1u) * arguments.kmer_size :
                                0;
    size_t const max_number_of_minimisers = arguments.pattern_size - arguments.window_size + 1;
    std::vector<size_t> const precomp_thresholds = compute_simple_model(arguments);

    // lambda captures all variables by reference
    auto worker = [&] (size_t const start, size_t const end)
    {
        // concurrent invocations of the membership agent are not thread safe
    // agent has to be created for each thread
	auto && agent = ibf.membership_agent();


    std::vector<query_result> thread_result{};    // set of query results processed by one thread
	std::set<size_t> sequence_hits{};     // bin hits for one sequence

	// vector holding all the minimisers and their starting position for the read
	using minimiser_vec_t = std::vector<std::tuple<uint64_t, size_t>>;
        minimiser_vec_t minimiser;

        auto hash_tuple_view = indexed_minimiser_hash(seqan3::ungapped{arguments.kmer_size},
                         	window_size{arguments.window_size},
                         	seed{adjust_seed(arguments.kmer_size)});

        for (auto && [id, seq] : records | seqan3::views::slice(start, end))
        {
	        sequence_hits.clear();

            minimiser = seq | hash_tuple_view | seqan3::views::to<minimiser_vec_t>;

//-----------------------------
//
// For each sliding window (pattern) the begin_vector shows the beginning of each sliding window
//
// If 	read_len = 150
// 	pattern_size = 50
// 	overlap = 30
//
// 	begin_vector = {0, 30, 60, 90, 100}
//
//-----------------------------
	    auto begin_vector = precalculate_begin(seq.size(), arguments.pattern_size, arguments.overlap);

//-----------------------------
// 
// Table of counting vectors newly created for each read
//	rows: each minimiser of read
// 	columns: each bin of IBF
//
//-----------------------------
	    using binning_bitvector_t = typename std::remove_cvref_t<decltype(ibf)>::membership_agent::binning_bitvector;
            std::vector<binning_bitvector_t> counting_table(minimiser.size(), 
                                              binning_bitvector_t(ibf.bin_count()));

	    // the beginning of the first window this minimiser is in
	    std::vector<size_t> window_span_begin(minimiser.size(), 0);
	    // the end of the last window this minimiser is in
            std::vector<size_t> window_span_end(minimiser.size(), 0);

	    for (size_t i{1}; i < minimiser.size(); i++)
            {
		const auto & [min, start_pos] = minimiser[i];
		window_span_begin[i] = start_pos;
		size_t end_pos = start_pos + arguments.window_size - 2; 
		window_span_end[i - 1] = end_pos;
		counting_table[i].raw_data() |= agent.bulk_contains(min).raw_data();
            }

	    window_span_end[minimiser.size() - 1] = seq.size() - 1;
	    minimiser.clear();

//-----------------------------
//
// If seq = CGCAAAACGCGGC
// 	p = 12
// 	w = 8
// 	k = 4
//
// minimiser 		= (AAAA; 3), (AAAC; 4), (AACG, 5)
// window_span_begin 	=     0		4	   5
// window_span_end 	=     10	11	   12
//
// minimiser	span
// AAAA		CGCAAAACGCG
// AAAC		AAACGCGG	
// AACG		AACGCGGC
//
//-----------------------------

            for (auto begin : begin_vector)
            {
		// indices for the first and last minimiser of the current sliding window
		std::vector<size_t>::iterator lower_it, upper_it;
		lower_it = std::lower_bound(window_span_begin.begin(), window_span_begin.end(), begin);
		upper_it = std::upper_bound(window_span_end.begin(), window_span_end.end(), 
				begin + arguments.pattern_size - 1); // - 1 because of 0 based indexing

		size_t first_index, last_index;
		first_index = lower_it - window_span_begin.begin();
		last_index = upper_it - window_span_end.begin() - 1; // - 1 because the upper bound returns the first el that is greater

		size_t const minimiser_count = last_index - first_index + 1;
		size_t const threshold = arguments.treshold_was_set ? 
		    			static_cast<size_t>(minimiser_count * arguments.threshold) :
                                         kmers_per_window == 1 ? kmer_lemma :
                                         precomp_thresholds[std::min(minimiser_count < min_number_of_minimisers ? 0 :
                                         minimiser_count - min_number_of_minimisers, 
					 // enrico recommended decreasing this value
					 max_number_of_minimisers - min_number_of_minimisers)] + 2;
     
	        // counting vector for the current pattern
		seqan3::counting_vector<uint8_t> total_counts(ibf.bin_count(), 0);
		
		for (size_t i = first_index; i <= last_index; i++)
                    total_counts += counting_table[i];
		for (size_t current_bin = 0; current_bin < total_counts.size(); current_bin++)
                {           
                    auto && count = total_counts[current_bin];
                    if (count >= threshold)
                    {
                        // the result_set is a union of results from all sliding windows of a read
                        sequence_hits.insert(current_bin);
                    }
                }
            }

            query_result query_result(id, sequence_hits);
            thread_result.emplace_back(query_result);

        }

        return thread_result;
    };

    for (auto && chunked_records : fin | seqan3::views::chunk((1ULL<<20)*10))
    {
        records.clear();
        auto start = std::chrono::high_resolution_clock::now();
        std::ranges::move(chunked_records, std::cpp20::back_inserter(records));
        auto end = std::chrono::high_resolution_clock::now();
        reads_io_time += std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

        cereal_handle.wait();

        do_parallel(worker, records.size(), synced_out, arguments.threads, compute_time);
    }

    if (arguments.write_time)
    {
        std::filesystem::path file_path{arguments.out_file};
        file_path += ".time";
        std::ofstream file_handle{file_path};
        file_handle << "IBF I/O\tReads I/O\tCompute\n";
        file_handle << std::fixed
                    << std::setprecision(2)
                    << ibf_io_time << '\t'
                    << reads_io_time << '\t'
                    << compute_time;
    }
}

} // namespace sliding_window
