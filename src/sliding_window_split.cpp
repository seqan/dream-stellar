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
    reference_metadata reference(arguments.ref_file, true);
    reference.to_file(arguments.ref_out);

    // Divide reference to segments that have at least min_len (doesn't take overlap into account)
    size_t segment_len = std::max(reference.total_len / arguments.min_bins, arguments.min_len);

    // For each segment assign start, length and bin number
    reference_segments segments(segment_len, arguments.overlap, reference.sequences);
    segments.to_file(arguments.seg_out);
}

void sliding_window_split(split_arguments const & arguments)
{
    // TODO: is there a need for a separate run_program function?
    // just added it to mirror search and build subroutines
    run_program(arguments);
}

} // namespace sliding_window::app