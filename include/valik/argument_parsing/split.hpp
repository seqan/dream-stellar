#pragma once

#include <valik/argument_parsing/shared.hpp>

namespace valik::app
{

void init_split_parser(sharg::parser & parser, split_arguments & arguments);
void run_split(sharg::parser & parser);

} // namespace valik::app
