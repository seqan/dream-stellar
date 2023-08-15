#pragma once

#include <valik/search/load_index.hpp>
#include <valik/search/query_record.hpp>
#include <valik/search/search_distributed.hpp>
#include <valik/search/search_local.hpp>
#include <valik/search/search_time_statistics.hpp>
#include <valik/shared.hpp>

namespace valik::app
{

void valik_search(search_arguments const & arguments);

} // namespace valik::app
