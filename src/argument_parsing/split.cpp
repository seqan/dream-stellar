#include <seqan3/core/debug_stream.hpp>

#include <valik/argument_parsing/split.hpp>
#include <valik/split/split.hpp>

namespace valik::app
{

void init_split_parser(sharg::parser & parser, split_arguments & arguments)
{
    init_shared_meta(parser);
    parser.add_positional_option(arguments.ref_file,
                      sharg::config{.description = "File containing reference sequences.",
                      .validator = sharg::input_file_validator{}});
    parser.add_option(arguments.ref_out,
                      sharg::config{.short_id = '\0',
                      .long_id = "ref-meta",
                      .description = "Please provide a valid path to the reference metadata output.",
                      .required = true,
                      .validator = sharg::output_file_validator{sharg::output_file_open_options::open_or_create}});
    parser.add_option(arguments.seg_out,
                      sharg::config{.short_id = '\0',
                      .long_id = "seg-meta",
                      .description = "Please provide a valid path to the segment metadata output.",
                      .required = true,
                      .validator = sharg::output_file_validator{sharg::output_file_open_options::open_or_create}});
    parser.add_option(arguments.overlap,
                      sharg::config{.short_id = '\0',
                      .long_id = "overlap",
                      .description = "Choose how much consecutive segments overlap.",
                      .validator = positive_integer_validator{true}});
    parser.add_option(arguments.bins,
                      sharg::config{.short_id = '\0',
                      .long_id = "bins",
                      .description = "Number of bins in the IBF. Multiples of 64 lead to better performance.",
                      .validator = sharg::arithmetic_range_validator{1, 29952}});
    parser.add_flag(arguments.write_seg,
                      sharg::config{.short_id = '\0',
                      .long_id = "write-out",
                      .description = "Write segment sequences to disk."});
}

void run_split(sharg::parser & parser)
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
