#pragma once

#include <sliding_window/argument_parsing/shared.hpp>

namespace sliding_window::app
{

void init_split_parser(seqan3::argument_parser & parser, split_arguments & arguments);
void run_split(seqan3::argument_parser & parser);

} // namespace sliding_window::app
