#include <gtest/gtest.h>

#include <valik/split/detail/helper.hpp>
#include <valik/shared.hpp>

TEST(find_segment_length, from_min_length)
{
    // case where segment length is estimated from minimum length
    valik::split_arguments arguments{};
    arguments.seg_len = 100;
    arguments.bins = 15;

    size_t total_len = 1000;
    valik::detail::set_segment_arguments(total_len, arguments);

    // user inputs min_len=100 and min_bins=15
    // estimate initial segment length based on whichever of the two inputs results in longer segments
    //      initial estimate for segment length 1000/15 = 66     <- from min_bins
    //      initial estimate for segment length 100              <- from min_len
    // pick the longer estimate i.e 100
    //      initial estimate for number of bins 1000/100 = 10
    // round to next power of two
    // number of bins = 16
    // actual segment length 1000/16 + 1 = 63
    size_t expected_bins = 16;
    size_t expected_len = 63;

    EXPECT_EQ(arguments.bins, expected_bins);
    EXPECT_EQ(arguments.seg_len, expected_len);

}

TEST(find_segment_length, from_min_nr_bins)
{
    // case where segment length is estimated from minimum number of bins
    valik::split_arguments arguments{};
    arguments.seg_len = 50;
    arguments.bins = 15;

    size_t total_len = 1000;
    valik::detail::set_segment_arguments(total_len, arguments);

    // user inputs min_len=50 and min_bins=15
    // estimate initial segment length based on whichever of the two inputs results in longer segments
    //      initial estimate for segment length 1000/15 = 66     <- from min_bins
    //      initial estimate for segment length 50               <- from min_len
    // pick the longer estimate i.e 66
    //      initial estimate for number of bins 1000/66 = 15
    // round to next power of two
    // number of bins = 16
    // actual segment length 1000/16 + 1 = 63
    size_t expected_bins = 16;
    size_t expected_len = 63;

    EXPECT_EQ(arguments.bins, expected_bins);
    EXPECT_EQ(arguments.seg_len, expected_len);
}
