#include <valik/split/detail/helper.hpp>

namespace valik::detail
{

// Compute power of two greater than or equal to n
// https://www.techiedelight.com/round-next-highest-power-2/
size_t next_power_of_two(size_t n)
{
    assert(n >= 1);

    // decrement n (to handle the case when n itself is a power of 2)
    n = n - 1;

    // calculate the position of the last set bit of n
    int lg = log2(n);

    // next power of two will have a bit set at position `lg+1`.
    return 1U << (lg + 1);
}

void set_segment_arguments(size_t total_len, split_arguments & arguments)
{
    assert(arguments.bins > 0);
    assert(arguments.seg_len > 0);

    // Divide reference into segments that have at least minimum length
    // Initial estimates based on user input
    size_t segment_len_estimate = std::max(total_len / arguments.bins, arguments.seg_len);
    assert(segment_len_estimate > 0);
    size_t num_bins_estimate = total_len / segment_len_estimate;

    // Round up number of bins to next power of two
    arguments.bins = next_power_of_two(num_bins_estimate);
    arguments.seg_len = total_len / arguments.bins + 1;
}

} // namespace valik::detail
