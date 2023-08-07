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
    database_metadata database(arguments.db_file, true);
    database.to_file(arguments.db_out);

    // For each segment assign start, length and bin number
    database_segments segments(arguments.seg_count, arguments.overlap, database);
    segments.to_file(arguments.seg_out);

    if (arguments.write_ref)
        write_reference_segments(database, segments, arguments.db_file);
    if (arguments.write_query)
        write_query_segments(database, segments, arguments.db_file);
}

} // namespace valik::app
