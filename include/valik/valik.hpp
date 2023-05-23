#pragma once

#include <sharg/all.hpp>

#include <valik/shared.hpp>

namespace valik::app
{

void try_parsing(sharg::parser & parser);
void init_top_level_parser(sharg::parser & parser);
void run_split(sharg::parser & parser);
void run_build(sharg::parser & parser);
void run_search(sharg::parser & parser);
void run_consolidation(sharg::parser & parser);

} // namespace valik::app
