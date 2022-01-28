#pragma once

#include <valik/argument_parsing/shared.hpp>

namespace valik::app
{

void init_build_parser(seqan3::argument_parser & parser, build_arguments & arguments);
void run_build(seqan3::argument_parser & parser);

} // namespace valik::app
