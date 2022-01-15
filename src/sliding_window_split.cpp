#include <sliding_window/shared.hpp>
#include <sliding_window/split/reference_metadata.hpp>
#include <sliding_window/split/reference_segments.hpp>

namespace sliding_window::app
{

//-----------------------------
//
// Divide reference database into partially overlapping segments and write metadata files.
//
//-----------------------------
void run_program(split_arguments const & arguments)
{    
    // Linear scan over reference file to extract metadata
    reference_metadata reference(arguments.ref_file);
    reference.to_file(arguments.ref_out);

    // Decide on number of bins and default length of segment (last segment of a reference sequence can have different length)
    uint32_t segment_len = arguments.min_len; 
    if (uint32_t(std::ceil(reference.total_len / arguments.min_bins)) <= arguments.min_len)
        segment_len = std::ceil(reference.total_len / arguments.min_bins); // divide reference into min nr of segments

    // For each segment assign start, length and bin number
    reference_segments segments(segment_len, arguments.overlap, reference.sequences);
    segments.to_file(arguments.seg_out);
    

    /* TODO: this belongs to IBF build subroutine

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
            
            for (auto && value : record.sequence() | seqan3::views::chunk(seg.start, seg.len) | hash_view)
            {
                ibf.emplace(value, seg.bin);
            }
            
        }
        i++;
    }
    */
}

void sliding_window_split(split_arguments const & arguments)
{
    // TODO: is there a need for a separate run_program function?
    // just added it to mirror search and build subroutines
    run_program(arguments);
}

} // namespace sliding_window::app