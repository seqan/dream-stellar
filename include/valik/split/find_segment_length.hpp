#include <valik/shared.hpp>
#include <valik/split/detail/next_power_of_two.hpp>

namespace valik
{

size_t find_segment_length(size_t total_len, split_arguments const & arguments)
{
    // Divide reference into segments that have at least minimum length
    // Initial estimates based on user input
    size_t segment_len_estimate = std::max(total_len / arguments.min_bins, arguments.min_len);
    size_t num_bins_estimate = total_len / segment_len_estimate;

    // Round up number of bins to next power of two
    size_t num_bins = next_power_of_two(num_bins_estimate);
    size_t segment_len = total_len / num_bins + 1;

    return segment_len;
}

} // namespace::valik
