#pragma once

#include <utilities/shared.hpp>
#include <valik/argument_parsing/shared.hpp>

namespace valik::app
{

void init_consolidation_parser(seqan3::argument_parser & parser, consolidation_arguments & arguments);
void run_consolidate(seqan3::argument_parser & parser);

} // namespace valik::app
