#include <seqan3/core/debug_stream.hpp>

#include <sliding_window/argument_parsing/split.hpp>
#include <sliding_window/split/split.hpp>

namespace sliding_window::app
{

void init_split_parser(seqan3::argument_parser & parser, split_arguments & arguments)
{
    init_shared_meta(parser);
    parser.add_positional_option(arguments.ref_file,
                      "File containing reference sequences.",
                      seqan3::input_file_validator{});
    parser.add_option(arguments.ref_out,
                      '\0',
                      "reference-output",
                      "Please provide a valid path to the reference metadata output.",
                      seqan3::option_spec::required,
                      seqan3::output_file_validator{});
    parser.add_option(arguments.seg_out,
                      '\0',
                      "segment-output",
                      "Please provide a valid path to the segment metadata output.",
                      seqan3::option_spec::required,
                      seqan3::output_file_validator{});
    parser.add_option(arguments.overlap,
                      '\0',
                      "overlap",
                      "Choose how much consecutive segments overlap.",
                      seqan3::option_spec::standard,
                      positive_integer_validator{true});
    parser.add_option(arguments.min_bins,
                      '\0',
                      "bins",
                      "How many bins should the IBF contain at a minimum.",
                      seqan3::option_spec::standard,
                      seqan3::arithmetic_range_validator{1, 30000});
    parser.add_option(arguments.min_len,
                      '\0',
                      "length",
                      "The minimum length of a reference segment.",
                      seqan3::option_spec::standard,
                      positive_integer_validator{true});
}

void run_split(seqan3::argument_parser & parser)
{
    split_arguments arguments{};
    init_split_parser(parser, arguments);
    try_parsing(parser);

    if (parser.is_option_set("overlap") & parser.is_option_set("length"))
    {
        if (arguments.overlap >= arguments.min_len)
            throw seqan3::argument_parser_error{"The overlap size has to be smaller than the segment length."};
    }

    // ==========================================
    // Dispatch
    // ==========================================
    sliding_window_split(arguments);
}

} // namespace sliding_window::app
