#include <seqan3/search/dream_index/interleaved_bloom_filter.hpp>
#include <seqan3/core/debug_stream.hpp>
#include <seqan3/utility/views/slice.hpp>   // provides views::slice

#include <sliding_window/search/compute_simple_model.hpp>
#include <sliding_window/search/do_parallel.hpp>
#include <sliding_window/search/load_ibf.hpp>
#include <sliding_window/search/sync_out.hpp>

#include <indexed_minimiser_hash.hpp>

namespace sliding_window
{

//---------------
// 
// Precalculate vector with all pattern begin positions in read. 
// This adds some computational overhead but makes the code much more readable.
//
//---------------
std::vector<size_t> precalculate_begin(size_t read_len, uint64_t pattern_size, uint64_t overlap)
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

//---------------
// 
// Find number of minimisers in sliding window.
// Necessary for calculating count threshold for (w,k)-minimisers.
//
//---------------
template <typename min_vec, size_t index> 
size_t find_minimiser_count(min_vec const & minimiser, size_t begin)  // no copy and can't modify minimiser
{
    
}


//---------------
//
// Search reads in IBF. 
//
//---------------
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

    auto agent = ibf.membership_agent();

    auto worker = [&] (size_t const start, size_t const end)
    {
        // evelin 
	auto counter = ibf.template counting_agent<uint16_t>();
        std::string result_string{};
	std::set<size_t> result_set{};

	// vector holding all the minimisers and their starting position for the read
        std::vector<std::tuple<uint64_t, size_t>> minimiser;

        auto hash_tuple_view = indexed_minimiser_hash(seqan3::ungapped{arguments.kmer_size},
                         	window_size{arguments.window_size},
                         	seed{adjust_seed(arguments.kmer_size)});

        for (auto && [id, seq] : records | seqan3::views::slice(start, end))
        {
	    result_set.clear();

            result_string.clear();
            result_string += id;
            result_string += '\t';

            minimiser = seq | hash_tuple_view | seqan3::views::to<std::vector<std::tuple<uint64_t, size_t>>>;            
	    auto begin_vector = precalculate_begin(seq.size(), arguments.pattern_size, arguments.overlap);

//---------------
// Table of counting vectors newly created for each read
//	rows: each minimiser of read
// 	columns: each bin of IBF
//
// 	TODO: instead of precomputing the whole table try to query certain regions of minimisers at a time.
//---------------
            std::vector<seqan3::counting_vector<uint8_t>> counting_table;
            counting_table.reserve(minimiser.size());

// Vector of minimiser start positions
	    std::vector<size_t> minimiser_positions;
	    minimiser_positions.reserve(minimiser.size());

// Vector of minimisers
	    std::vector<uint64_t> minimiser_values;
	    minimiser_values.reserve(minimiser.size());

            for (auto [min,pos] : minimiser)
            {
		// TODO: why doesn't this work?
		// auto counts = agent.bulk_contains(min); 
		seqan3::counting_vector<uint8_t> counts(ibf.bin_count(), 0);
                counts += agent.bulk_contains(min);
                counting_table.push_back(counts);
		minimiser_positions.push_back(pos);
		minimiser_values.push_back(min);
            }
	    
	    //minimiser.clear();

//---------------
// For each sliding window
//---------------
            for (auto begin : begin_vector)
            {
		std::vector<size_t>::iterator pattern_first, pattern_last;

// Indices for the first and last minimiser that are in the current sliding window
		pattern_first = std::lower_bound(minimiser_positions.begin(), minimiser_positions.end(), begin);
		pattern_last = std::upper_bound(minimiser_positions.begin(), minimiser_positions.end(), 
				begin + arguments.pattern_size - arguments.kmer_size - 1);

		std::size_t first_index = std::distance(std::begin(minimiser_positions), pattern_first);
		std::size_t last_index = std::distance(std::begin(minimiser_positions), pattern_last);
                if (last_index == minimiser_positions.size())
                    last_index--; // if last minimiser of read


		// TODO: might use this to query one slice at a time?
   		// auto sliding_window_slice = minimiser_values | seqan3::views::slice(0,4);
		size_t const minimiser_count = last_index - first_index + 1;

//---------------
// Need minimiser count for each window to be able to do probabilistic thresholding
// 1. is threshold set manually?
// 2. elif w = k -> use k-mer lemma
// 3. else use a precomputed table of thresholds to look up the value that corresponds to the number of minimisers
// in the pattern, w and k.
//---------------
		size_t const threshold = arguments.treshold_was_set ? 
		    			static_cast<size_t>(minimiser_count * arguments.threshold) :
                                         kmers_per_window == 1 ? kmer_lemma :
                                         precomp_thresholds[std::min(minimiser_count < min_number_of_minimisers ? 0 :
                                         minimiser_count - min_number_of_minimisers, 
					 // enrico recommended decreasing this value
					 max_number_of_minimisers - min_number_of_minimisers)] + 2;
     

		seqan3::counting_vector<uint8_t> total_counts(ibf.bin_count(), 0);

		for (size_t i = first_index; i <= last_index; i++)
		{
                    total_counts += counting_table[i];
                }
                for (size_t current_bin = 0; current_bin < total_counts.size(); current_bin++)
                {           
                    auto && count = total_counts[current_bin];
                    if (count >= threshold)
                    {
                        // the result_set is a union of results from all sliding windows of a read
                        result_set.insert(current_bin);
                    }
                }
            }

//---------- 
//
// Write out union of bin hits over all patterns
//
//---------- 
            for (auto bin : result_set)
            {
                result_string += std::to_string(bin);
                result_string += ',';
            }

            result_string += '\n';
            synced_out.write(result_string);

        }
    };

    for (auto && chunked_records : fin | seqan3::views::chunk((1ULL<<20)*10))
    {
        records.clear();
        auto start = std::chrono::high_resolution_clock::now();
        std::ranges::move(chunked_records, std::cpp20::back_inserter(records));
        auto end = std::chrono::high_resolution_clock::now();
        reads_io_time += std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

        cereal_handle.wait();

        do_parallel(worker, records.size(), arguments.threads, compute_time);
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
