#include <valik/argument_parsing/top_level.hpp>

namespace valik::app
{

void init_top_level_parser(sharg::parser & parser)
{
    init_shared_meta(parser);
    parser.info.description.emplace_back("Find local alignments between sets of DNA sequences.");

    parser.info.examples = {"./dream-stellar build --help", "./dream-stellar search --help"};
}

} // namespace valik::app
