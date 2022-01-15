#include <sliding_window/argument_parsing/top_level.hpp>

namespace sliding_window::app
{

void init_top_level_parser(seqan3::argument_parser & parser)
{
    init_shared_meta(parser);
    parser.info.description.emplace_back("Binning Directories are a datastruture that can be used in various ways. "
                                         "What's a bin, how can it be used, etc.");

    parser.info.examples = {"./sliding_window split --help", "./sliding_window build --help", "./sliding_window search --help"};
};

} // namespace sliding_window::app
