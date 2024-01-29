#pragma once

#include <valik/argument_parsing/shared.hpp>
#include <valik/build/build.hpp>
#include <valik/split/metadata.hpp>
#include <utilities/threshold/io.hpp>
#include <utilities/threshold/find.hpp>

namespace valik::app
{

void init_build_parser(sharg::parser & parser, build_arguments & arguments);
void run_build(sharg::parser & parser);

} // namespace valik::app
