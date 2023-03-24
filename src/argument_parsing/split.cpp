#include <seqan3/core/debug_stream.hpp>

#include <valik/argument_parsing/split.hpp>
#include <valik/split/split.hpp>

namespace valik::app
{

void init_split_parser(seqan3::argument_parser & parser, split_arguments & arguments)
{
    init_shared_meta(parser);
    parser.add_positional_option(arguments.ref_file,
                      "File containing reference sequences.",
                      seqan3::input_file_validator{});
    parser.add_option(arguments.ref_out,
                      '\0',
                      "ref-meta",
                      "Please provide a valid path to the reference metadata output.",
                      seqan3::option_spec::required,
                      seqan3::output_file_validator{seqan3::output_file_open_options::open_or_create});
    parser.add_option(arguments.seg_out,
                      '\0',
                      "seg-meta",
                      "Please provide a valid path to the segment metadata output.",
                      seqan3::option_spec::required,
                      seqan3::output_file_validator{seqan3::output_file_open_options::open_or_create});
    parser.add_option(arguments.overlap,
                      '\0',
                      "overlap",
                      "Choose how much consecutive segments overlap.",
                      seqan3::option_spec::standard,
                      positive_integer_validator{true});
    parser.add_option(arguments.bins,
                      '\0',
                      "bins",
                      "Number of bins in the IBF. Multiples of 64 lead to better performance.",
                      seqan3::option_spec::standard,
                      seqan3::arithmetic_range_validator{1, 29952});
    parser.add_flag(arguments.write_seg,
                      '\0',
                      "write-out",
                      "Write segment sequences to disk.");
}

void run_split(seqan3::argument_parser & parser)
{
    split_arguments arguments{};
    init_split_parser(parser, arguments);
    try_parsing(parser);

    // ==========================================
    // Dispatch
    // ==========================================
    valik_split(arguments);
}

} // namespace valik::app
