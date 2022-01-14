#pragma once

#include <sliding_window/split_reference/reference_metadata.hpp>
#include <sliding_window/split_reference/reference_segments.hpp>

void run_split()
{    
    size_t overlap = 150; // Should this be minimum local match length or read length?

    // Constraints for reasonably sized segments
    size_t min_nr_bins = 64; // IBF should have at least this many bins to allow to be concurrent "enough"
    uint32_t min_bin_len = 3 * 10e6; // segments should not be "too short"

    // Linear scan over reference file to extract metadata
    std::string filename = "/home/evelin/metagenomics/test-dream-stellar/read-mapping/dmel.fasta";
    reference_metadata reference(filename);
    reference.to_file("../reference_metadata.txt");

    // Decide on number of bins and default length of segment (last segment of a reference sequence can have different length)
    uint32_t segment_len = min_bin_len; 
    if (uint32_t(std::ceil(reference.total_len / min_nr_bins)) <= min_bin_len)
        segment_len = std::ceil(reference.total_len / min_nr_bins); // divide reference into min nr of segments

    // For each segment assign start, length and bin number
    reference_segments segments(segment_len, overlap, reference.sequences);
    segments.to_file("../reference_segments.txt");
    

    // Second linear scan over reference database
    seqan3::sequence_file_input fin{filename};

    int i = 0;
    for (auto & record : fin)
    {
        // get the relevant segments for each reference
        auto ref_seg = [&](reference_segments::segment & seg) {return reference.sequences.at(i).id == seg.ref_id;};
        for (auto & seg : segments.members | std::views::filter(ref_seg))
        {
            // TODO: actually create the IBF and hash view first
            /*
            for (auto && value : record.sequence() | seqan3::views::chunk(seg.start, seg.len) | hash_view)
            {
                ibf.emplace(value, seg.bin);
            }
            */
        }
        i++;
    }
    
    return 0;
}
