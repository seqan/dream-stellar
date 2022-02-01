#include <gtest/gtest.h>

#include <valik/search/search_setup.hpp>
#include <valik/shared.hpp>
#include <valik/search/compute_simple_model.hpp>

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

// ====================================================================================
//
// seq = CGCAAAACGCGGC
// 	p = 12
// 	w = 8
// 	k = 4
//
// minimiser	             span_begin    minimiser belongs to windows starting at
// AAAA		CGCAAAACGCG          0                      0, 1, 2, 3
// AAAC		    AAACGCGG         4                          4
// AACG		     AACGCGGC        5                          5
//
// ====================================================================================

TEST(make_pattern_bounds, first_pattern_of_query)
{
    // normal case where pattern starts from beginning of query
    valik::search_arguments arguments{};
    arguments.pattern_size = 12;
    arguments.window_size = 8;
    arguments.kmer_size = 4;
    arguments.errors = 1;

    std::vector<size_t> const & window_span_begin{0, 4, 5};

    size_t const pattern_begin = 0;
    valik::pattern_bounds expected{};

    //
    // |CGCA*AAACGCGG|C
    //
    // last window of the pattern start at (0 + 12 - 8) = 4 (*)
    // pattern windows start at 0, 1, 2, 3, 4
    //
    // minimisers [0, 1] = [0; 2)
    expected.begin_position = 0;
    expected.end_position = 2;

    valik::threshold threshold_data = valik::make_threshold_data(arguments);
    valik::pattern_bounds bounds = valik::make_pattern_bounds(pattern_begin, arguments, window_span_begin, threshold_data);

    EXPECT_EQ(bounds.begin_position, expected.begin_position);
    EXPECT_EQ(bounds.end_position, expected.end_position);
}

TEST(make_pattern_bounds, same_minimiser_consecutive_windows_begin)
{
    // special case where pattern starts after the first of multiple consecutive minimisers
    // and pattern ends at the end of the query
    valik::search_arguments arguments{};
    arguments.pattern_size = 12;
    arguments.window_size = 8;
    arguments.kmer_size = 4;
    arguments.errors = 1;


    std::vector<size_t> const & window_span_begin{0, 4, 5};

    size_t const pattern_begin = 1;
    valik::pattern_bounds expected{};

    //
    // C|GCAA*AACGCGGC|
    //
    // last window of the pattern start at (1 + 12 - 8) = 5 (*)
    // pattern windows start at 1, 2, 3, 4, 5
    //
    // minimisers [0, 2] = [0; 3)
    expected.begin_position = 0;
    expected.end_position = 3;

    valik::threshold threshold_data = valik::make_threshold_data(arguments);
    valik::pattern_bounds bounds = valik::make_pattern_bounds(pattern_begin, arguments, window_span_begin, threshold_data);

    EXPECT_EQ(bounds.begin_position, expected.begin_position);
    EXPECT_EQ(bounds.end_position, expected.end_position);
}

TEST(make_pattern_bounds, pattern_equals_window)
{
    // special case where pattern_size == window_size
    valik::search_arguments arguments{};
    arguments.pattern_size = 8;
    arguments.window_size = 8;
    arguments.kmer_size = 4;
    arguments.errors = 1;


    std::vector<size_t> const & window_span_begin{0, 4, 5};

    size_t const pattern_begin = 1;
    valik::pattern_bounds expected{};

    //
    // C|*GCAAAACG|CGGC
    //
    // last window of the pattern start at (1 + 8 - 8) = 1 (*)
    // pattern windows start at 1
    //
    // minimisers [0] = [0; 1)
    expected.begin_position = 0;
    expected.end_position = 1;

    valik::threshold threshold_data = valik::make_threshold_data(arguments);
    valik::pattern_bounds bounds = valik::make_pattern_bounds(pattern_begin, arguments, window_span_begin, threshold_data);

    EXPECT_EQ(bounds.begin_position, expected.begin_position);
    EXPECT_EQ(bounds.end_position, expected.end_position);
}

// ====================================================================================
//
// seq = CCACGTCGAAGGTT
// 	p = 12
// 	w = 8
// 	k = 4
//
// minimiser	             span_begin     minimiser belongs to windows starting at
// ACGT		CCACGTCGAA           0                           0, 1, 2
// CGAA        CGTCGAAG          3                              3
// AAGG         GTCGAAGGT        4                             4, 5
// aacc           CGAAGGTT       6                              6
// ====================================================================================

TEST(make_pattern_bounds, same_minimiser_consecutive_windows_end)
{
    // special case where pattern ends after the first of multiple consecutive minimisers
    valik::search_arguments arguments{};
    arguments.pattern_size = 12;
    arguments.window_size = 8;
    arguments.kmer_size = 4;
    arguments.errors = 1;

    std::vector<size_t> const & window_span_begin{0, 3, 4, 6};

    size_t const pattern_begin = 0;
    valik::pattern_bounds expected{};

    //
    // |CCAC*GTCGAAGG|TT
    //
    // last window of the pattern start at (0 + 12 - 8) = 4 (*)
    // pattern windows start at 0, 1, 2, 3, 4
    //
    // minimisers [0, 2] = [0; 3)
    expected.begin_position = 0;
    expected.end_position = 3;

    valik::threshold threshold_data = valik::make_threshold_data(arguments);
    valik::pattern_bounds bounds = valik::make_pattern_bounds(pattern_begin, arguments, window_span_begin, threshold_data);

    EXPECT_EQ(bounds.begin_position, expected.begin_position);
    EXPECT_EQ(bounds.end_position, expected.end_position);
}

// ====================================================================================
// seq = CCACGTCGAAGGTT
// 	p = 12
// 	w = 8
// 	k = 4
//
// minimiser	             span_begin     minimiser belongs to windows starting at
// ACGT		CCACGTCGA            0                          0, 1, 2
// CGAA        CGTCGAAG          3                            3, 4
// AAGG          TCGAAGGT        5                            5, 6
// aacc            GAAGGTT       7                              7
// ====================================================================================

TEST(make_pattern_bounds, odd_lengths)
{
    // normal case where kmer size is not divisible by window or pattern size
    valik::search_arguments arguments{};
    arguments.pattern_size = 11;
    arguments.window_size = 7;
    arguments.kmer_size = 4;
    arguments.errors = 1;

    std::vector<size_t> const & window_span_begin{0, 3, 5, 7};

    size_t const pattern_begin = 2;
    valik::pattern_bounds expected{};

    //
    // CC|ACGT*CGAAGGT|T
    //
    // last window of the pattern start at (2 + 11 - 7) = 6 (*)
    // pattern windows start at 2, 3, 4, 5, 6
    //
    // minimisers [0, 2] = [0; 3)
    expected.begin_position = 0;
    expected.end_position = 3;

    valik::threshold threshold_data = valik::make_threshold_data(arguments);
    valik::pattern_bounds bounds = valik::make_pattern_bounds(pattern_begin, arguments, window_span_begin, threshold_data);

    EXPECT_EQ(bounds.begin_position, expected.begin_position);
    EXPECT_EQ(bounds.end_position, expected.end_position);
}
