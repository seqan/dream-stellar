#include <cmath>

namespace valik
{

// Compute power of two greater than or equal to n
// https://www.techiedelight.com/round-next-highest-power-2/
size_t next_power_of_two(size_t n)
{
    // decrement n (to handle the case when n itself is a power of 2)
    n = n - 1;

    // calculate the position of the last set bit of n
    int lg = log2(n);

    // next power of two will have a bit set at position `lg+1`.
    return 1U << lg + 1;
}

} // namespace::valik
