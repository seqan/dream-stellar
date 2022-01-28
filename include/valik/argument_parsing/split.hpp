#pragma once

#include <valik/argument_parsing/shared.hpp>

namespace valik::app
{

void init_split_parser(seqan3::argument_parser & parser, split_arguments & arguments);
void run_split(seqan3::argument_parser & parser);

} // namespace valik::app
