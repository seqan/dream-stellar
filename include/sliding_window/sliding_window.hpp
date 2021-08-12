#pragma once

#include <sliding_window/shared.hpp>

namespace sliding_window
{

void try_parsing(seqan3::argument_parser & parser);
void init_top_level_parser(seqan3::argument_parser & parser);
void run_build(seqan3::argument_parser & parser);
void run_search(seqan3::argument_parser & parser);

} // namespace sliding_window
