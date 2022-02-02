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

size_t find_segment_length(size_t total_len, size_t min_len, size_t min_bins)
{
    assert(min_bins > 0);
    assert(min_len > 0);

    // Divide reference into segments that have at least minimum length
    // Initial estimates based on user input
    size_t segment_len_estimate = std::max(total_len / min_bins, min_len);
    assert(segment_len_estimate > 0);
    size_t num_bins_estimate = total_len / segment_len_estimate;

    // Round up number of bins to next power of two
    size_t num_bins = next_power_of_two(num_bins_estimate);
    size_t segment_len = total_len / num_bins + 1;

    return segment_len;
}

} // namespace valik::detail
