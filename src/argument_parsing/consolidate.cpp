#include <valik/argument_parsing/consolidate.hpp>
#include <valik/consolidate/consolidate.hpp>

namespace valik::app
{

void init_consolidation_parser(seqan3::argument_parser & parser, consolidation_arguments & arguments)
{
    init_shared_meta(parser);
    parser.add_option(arguments.matches_in,
                      'i',
                      "input",
                      "DREAM Stellar matches.",
                      seqan3::option_spec::required,
                      seqan3::input_file_validator{{"gff"}});
    parser.add_option(arguments.seg_path,
                    '\0',
                    "seg-path",
                    "Path to segment metadata file created by split.",
                    seqan3::option_spec::standard,
                    seqan3::input_file_validator{});
    parser.add_option(arguments.matches_out,
                      'o',
                      "output",
                      "Consolidated output.",
                      seqan3::option_spec::required,
                      seqan3::input_file_validator{{"gff"}});
}

void run_consolidation(seqan3::argument_parser & parser)
{
    consolidation_arguments arguments{};
    init_consolidation_parser(parser, arguments);
    try_parsing(parser);

    valik_consolidate(arguments);
}

} // namespace valik::app
