#pragma once

#include <valik/argument_parsing/validators.hpp>
#include <valik/shared.hpp>

namespace valik::app
{

void init_shared_meta(seqan3::argument_parser & parser);
void try_parsing(seqan3::argument_parser & parser);

template <typename arguments_t>
void init_shared_options(seqan3::argument_parser & parser, arguments_t & arguments)
{
    static_assert(std::same_as<arguments_t, build_arguments> || std::same_as<arguments_t, search_arguments>);

    // TODO: split cannot be run multi-threaded
    parser.add_option(arguments.threads,
                      '\0',
                      "threads",
                      "Choose the number of threads.",
                      seqan3::option_spec::standard,
                      positive_integer_validator{});
}

} // namespace valik::app
