#include <valik/argument_parsing/shared.hpp>
#include <valik/shared.hpp>
#include <valik/split/metadata.hpp>
#include <valik/split/write_seg_sequences.hpp>

namespace valik::app
{

/**
 * @brief Function that divides reference or query database into partially overlapping segments.
 *
 * @param arguments Command line arguments.
 */
void valik_split(split_arguments & arguments)
{
    if (arguments.split_index)
        arguments.seg_count = adjust_bin_count(arguments.seg_count_in);
    else
        arguments.seg_count = arguments.seg_count_in;

    metadata meta(arguments);
    meta.to_file(arguments.meta_out);

    if (arguments.write_ref)
        write_reference_segments(meta, arguments.meta_out);
    if (arguments.write_query)
        write_query_segments(meta, arguments.meta_out);
}

} // namespace valik::app
