#pragma once

#include <sliding_window/argument_parsing/shared.hpp>

namespace sliding_window::app
{

void init_search_parser(seqan3::argument_parser & parser, search_arguments & arguments);
void run_search(seqan3::argument_parser & parser);

} // namespace sliding_window::app
