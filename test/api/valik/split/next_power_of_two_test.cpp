#include <gtest/gtest.h>

#include <valik/split/detail/helper.hpp>

TEST(next_power_of_two, one)
{
    // special case where n == 1 skip 2^0
    size_t nr_bins = valik::detail::next_power_of_two(1u);
    size_t expected = 2;

    EXPECT_EQ(nr_bins, expected);
}

TEST(next_power_of_two, not_power_of_two)
{
    // case where n is not a power of two
    size_t nr_bins = valik::detail::next_power_of_two(17u);
    size_t expected = 32;

    EXPECT_EQ(nr_bins, expected);
}

TEST(next_power_of_two, power_of_two)
{
    // case where n is already a power of two
    size_t nr_bins = valik::detail::next_power_of_two(64u);
    size_t expected = 64;

    EXPECT_EQ(nr_bins, expected);
}
