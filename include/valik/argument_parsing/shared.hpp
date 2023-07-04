#pragma once

#include <valik/argument_parsing/validators.hpp>
#include <valik/shared.hpp>

namespace valik::app
{

void init_shared_meta(sharg::parser & parser);
void try_parsing(sharg::parser & parser);

} // namespace valik::app
