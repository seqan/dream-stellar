#pragma once

#include <utilities/shared.hpp>
#include <valik/argument_parsing/shared.hpp>

namespace valik::app
{

void init_consolidation_parser(sharg::parser & parser, consolidation_arguments & arguments);
void run_consolidate(sharg::parser & parser);

} // namespace valik::app
