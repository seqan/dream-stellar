#include <gtest/gtest.h>

#include <valik/search/search_setup.hpp>

TEST(pattern_begin_positions, read_length_and_pattern_size_are_equal)
{
    // edge case where read_len = pattern_size
    size_t const read_len = 150u;
    uint64_t const pattern_size = read_len;
    uint64_t const overlap = 30u;

    std::vector<size_t> begin_positions{};
    std::vector<size_t> expected{0u}; // pattern interval [0, 150]

    valik::pattern_begin_positions(read_len, pattern_size, overlap, [&](size_t const begin)
    {
        begin_positions.push_back(begin);
    });

    EXPECT_EQ(begin_positions, expected); // seen all positions
}

TEST(pattern_begin_positions, overlaps_are_evenly)
{
    // special case where read_len - pattern_size is exactly the last possible begin position
    size_t const read_len = 150u;
    uint64_t const pattern_size = 50u;
    uint64_t const overlap = 30u;

    std::vector<size_t> begin_positions{};
    std::vector<size_t> expected = {
        0u, // pattern interval [0, 50]
        0u + pattern_size - overlap /* 20u */, // pattern interval [20, 70]
        20u + pattern_size - overlap /* 40u */, // pattern interval [40, 90]
        60u, // pattern interval [60, 110]
        80u, // pattern interval [80, 130]
        // pattern interval [100, 150]
        100u // ends here, because read_len - pattern_size = 100u
    };

    valik::pattern_begin_positions(read_len, pattern_size, overlap, [&](size_t const begin)
    {
        begin_positions.push_back(begin);
    });

    EXPECT_EQ(begin_positions, expected); // seen all positions
}

TEST(pattern_begin_positions, extra_overlap)
{
    // normal case where read_len - pattern_size has room for an additional element
    size_t const read_len = 150;
    uint64_t const pattern_size = 50;
    uint64_t const overlap = 20;

    std::vector<size_t> begin_positions{};
    std::vector<size_t> expected = {
        0u, // pattern interval [0, 50]
        0u + pattern_size - overlap /* 30u */, // pattern interval [30, 80]
        30u + pattern_size - overlap /* 60u */, // pattern interval [60, 110]
        90u, // pattern interval [90, 140]
        // pattern interval [100, 150]
        100u // ends here, because read_len - pattern_size = 110u
    };

    valik::pattern_begin_positions(read_len, pattern_size, overlap, [&](size_t const begin)
    {
        begin_positions.push_back(begin);
    });

    EXPECT_EQ(begin_positions, expected); // seen all positions
}
