#pragma once

#include "iostream"

#include <utilities/external_process.hpp>
#include <valik/search/env_var_pack.hpp>
#include <valik/search/execution_metadata.hpp>
#include <valik/shared.hpp>

namespace valik
{

/**
 * @brief Function that merges search results and metadata across threads.
 *
 * @param arguments Command line arguments.
 * @param time_statistics Run time statistics. IN-OUT parameter.
 * @param exec_meta Metadata table across all search threads.
 * @param var_pack Environmental variables, this function calls the merge executable.
 * @return false if merge failed.
 */
bool merge_processes(search_arguments const & arguments,
                     app::search_time_statistics & time_statistics,
                     app::execution_metadata & exec_meta,
                     env_var_pack const & var_pack);

}   // namespace valik
