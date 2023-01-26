#pragma once

#include <valik/argument_parsing/shared.hpp>

namespace valik::app
{

void init_consolidation_parser(seqan3::argument_parser & parser, consolidation_arguments & arguments);
void run_consolidation(seqan3::argument_parser & parser);

} // namespace valik::app
