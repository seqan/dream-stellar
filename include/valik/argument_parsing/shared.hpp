#pragma once

#include <valik/argument_parsing/validators.hpp>
#include <valik/shared.hpp>

namespace valik::app
{

void init_shared_meta(sharg::parser & parser);
void try_parsing(sharg::parser & parser);

template <typename arguments_t>
void init_shared_options(sharg::parser & parser, arguments_t & arguments)
{
    static_assert(std::same_as<arguments_t, build_arguments> || std::same_as<arguments_t, search_arguments>);

    parser.add_option(arguments.threads,
                      sharg::config{.short_id = '\0',
                      .long_id = "threads",
                      .description = "Choose the number of threads.",
                      .validator = positive_integer_validator{}});
}

} // namespace valik::app
