#pragma once

#include <utilities/threshold/find.hpp>
#include <valik/argument_parsing/shared.hpp>

namespace valik::app
{

void init_search_parser(sharg::parser & parser, search_arguments & arguments);
void run_search(sharg::parser & parser);

} // namespace valik::app
