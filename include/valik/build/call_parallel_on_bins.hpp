#pragma once

#include <seqan3/core/algorithm/detail/execution_handler_parallel.hpp>
#include <seqan3/utility/views/chunk.hpp>

#include <valik/shared.hpp>

namespace valik
{

template <typename algorithm_t>
void call_parallel_on_bins(algorithm_t && worker, build_arguments const & arguments)
{
    size_t const chunk_size = std::clamp<size_t>(std::bit_ceil(arguments.bins / arguments.threads),
                                                 8u,
                                                 64u); // each thread will process between 8 to 64 bins
    auto chunked_view = seqan3::views::zip(arguments.bin_path, std::views::iota(0u)) | // pair each database input file in the bin_path vector with bin number
                        seqan3::views::chunk(chunk_size); // how many input files are processed by each thread
    seqan3::detail::execution_handler_parallel executioner{arguments.threads};
    executioner.bulk_execute(std::move(worker), std::move(chunked_view), [](){});
}

} // namespace valik
