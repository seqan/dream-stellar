#pragma once

#include <sliding_window/argument_parsing/shared.hpp>

namespace sliding_window::app
{

void init_build_parser(seqan3::argument_parser & parser, build_arguments & arguments);
void run_build(seqan3::argument_parser & parser);

} // namespace sliding_window::app
