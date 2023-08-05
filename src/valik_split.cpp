#include <valik/argument_parsing/shared.hpp>
#include <valik/shared.hpp>
#include <valik/split/database_metadata.hpp>
#include <valik/split/database_segments.hpp>
#include <valik/split/write_seg_sequences.hpp>

namespace valik::app
{

//-----------------------------
//
// Divide reference database into partially overlapping segments.
//
//-----------------------------
void valik_split(split_arguments const & arguments)
{
    // Linear scan over reference file to extract metadata
    database_metadata reference(arguments.ref_file, true);
    reference.to_file(arguments.ref_out);

    // For each segment assign start, length and bin number
    database_segments segments(arguments.bins, arguments.overlap, reference);
    segments.to_file(arguments.seg_out);

    if (arguments.write_seg)
        write_seg_sequences<seqan3::dna4>(reference, segments, arguments.ref_file);
}

} // namespace valik::app
