#include <utilities/argument_parsing/consolidate.hpp>
#include <utilities/consolidate/consolidate.hpp>

namespace valik::app
{

void init_consolidation_parser(sharg::parser & parser, consolidation_arguments & arguments)
{
    init_shared_meta(parser);
    parser.add_option(arguments.matches_in,
                      sharg::config{.short_id = 'i',
                      .long_id = "input",
                      .description = "DREAM Stellar matches.",
                      .required = true,
                      .validator = sharg::input_file_validator{{"gff"}}});
    parser.add_option(arguments.ref_meta_path,
                    sharg::config{.short_id = '\0',
                    .long_id = "ref-meta",
                    .description = "Path to reference metadata file created by split.",
                    .validator = sharg::input_file_validator{}});
    parser.add_option(arguments.matches_out,
                      sharg::config{.short_id = 'o',
                      .long_id = "output",
                      .description = "Consolidated output.",
                      .required = true,
                      .validator = sharg::output_file_validator{sharg::output_file_open_options::open_or_create, {"gff"}}});
}

void run_consolidation(sharg::parser & parser)
{
    consolidation_arguments arguments{};
    init_consolidation_parser(parser, arguments);
    try_parsing(parser);

    valik_consolidate(arguments);
}

} // namespace valik::app
