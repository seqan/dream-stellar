#include <valik/argument_parsing/shared.hpp>
#include <valik/shared.hpp>
#include <valik/split/reference_metadata.hpp>
#include <valik/split/reference_segments.hpp>

namespace valik::app
{

//-----------------------------
//
// Divide reference database into partially overlapping segments and write metadata files.
//
//-----------------------------
void valik_split(split_arguments & arguments)
{
    // Linear scan over reference file to extract metadata
    reference_metadata reference(arguments.ref_file, true);
    reference.to_file(arguments.ref_out);

    // For each segment assign start, length and bin number
    reference_segments segments(arguments.bins, arguments.overlap, reference);
    segments.to_file(arguments.seg_out);
}

} // namespace valik::app
