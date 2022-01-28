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
void valik_split(split_arguments const & arguments)
{
    // Linear scan over reference file to extract metadata
    reference_metadata reference(arguments.ref_file, true);
    reference.to_file(arguments.ref_out);

    // Divide reference to segments that have at least min_len (doesn't take overlap into account)
    // TODO: round up number of bins to next power of two
    size_t segment_len = std::max(reference.total_len / arguments.min_bins, arguments.min_len);

    if (reference.total_len < segment_len)
    {
        throw seqan3::argument_parser_error{"The segment length is greater than the total length of the reference."};
    }

    // For each segment assign start, length and bin number
    reference_segments segments(segment_len, arguments.overlap, reference.sequences);
    segments.to_file(arguments.seg_out);
}

} // namespace valik::app
