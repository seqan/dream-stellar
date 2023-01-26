#include <valik/argument_parsing/top_level.hpp>

namespace valik::app
{

void init_top_level_parser(seqan3::argument_parser & parser)
{
    init_shared_meta(parser);
    parser.info.description.emplace_back("Binning Directories are a datastruture that can be used in various ways. "
                                         "What's a bin, how can it be used, etc.");

    parser.info.examples = {"./valik split --help", "./valik build --help", "./valik search --help", "./valik consolidate --help"};
}

} // namespace valik::app
