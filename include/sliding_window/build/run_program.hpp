#pragma once

#include <sliding_window/build/ibf_factory.hpp>
#include <sliding_window/build/store_index.hpp>
#include <sliding_window/split/reference_metadata.hpp>
#include <sliding_window/split/reference_segments.hpp>

#include <seqan3/search/dream_index/interleaved_bloom_filter.hpp>
#include <seqan3/search/views/minimiser_hash.hpp>
#include <seqan3/utility/views/slice.hpp>

namespace sliding_window
{

// TODO: refactor: for split and search subroutines run_program is placed in sliding_window::app files  
template <bool compressed>
void run_program(build_arguments const & arguments)
{
    if (arguments.from_segments)
    {
        reference_segments segments(arguments.seg_path);
        reference_metadata reference(arguments.ref_meta_path, false);

        seqan3::sequence_file_input fin{arguments.bin_file};

        seqan3::interleaved_bloom_filter<> ibf{seqan3::bin_count{arguments.bins}, // TODO: should nr of bins be power of two?
                                               seqan3::bin_size{arguments.bits},
                                               seqan3::hash_function_count{arguments.hash}};

        auto hash_view = seqan3::views::minimiser_hash(seqan3::ungapped{arguments.kmer_size},
                                                     seqan3::window_size{arguments.window_size},
                                                     seqan3::seed{adjust_seed(arguments.kmer_size)});

        int i = 0;
        for (auto & record : fin)
        {
            // get the relevant segments for each reference
            auto ref_seg = [&](reference_segments::segment & seg) {return reference.sequences.at(i).id == seg.ref_id;};
            for (auto & seg : segments.members | std::views::filter(ref_seg))
            {   
                for (auto && value : record.sequence() | seqan3::views::slice(seg.start, seg.start + seg.len) | hash_view)
                    ibf.emplace(value, seqan3::bin_index(seg.bin));
            }
            i++;
        }

        store_index(arguments.out_path, ibf, arguments);
    }
    else
    {
        ibf_factory<compressed> generator{arguments};
        auto ibf = generator();
        store_index(arguments.out_path, ibf, arguments);
    }
}

} // namespace sliding_window
