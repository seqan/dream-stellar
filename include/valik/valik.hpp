#pragma once

#include <seqan3/argument_parser/argument_parser.hpp>

#include <valik/shared.hpp>

namespace valik::app
{

void try_parsing(seqan3::argument_parser & parser);
void init_top_level_parser(seqan3::argument_parser & parser);
void run_split(seqan3::argument_parser & parser);
void run_build(seqan3::argument_parser & parser);
void run_search(seqan3::argument_parser & parser);
void run_consolidation(seqan3::argument_parser & parser);

} // namespace valik::app
