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

//----------------------------------------------------------
//
// seq = CGCAAAACGCGGC
// 	p = 12
// 	w = 8
// 	k = 4
//
// minimiser	             span
// AAAA		CGCAAAACGCG     [0, 11)
// AAAC		    AAACGCGG    [4, 12)
// AACG		     AACGCGGC   [5, 13)
//
//----------------------------------------------------------

TEST(make_pattern_bounds, first_pattern_of_query)
{
    // normal case where pattern starts from beginning of query
    valik::search_arguments arguments{};
    arguments.pattern_size = 12;
    arguments.window_size = 8;
    arguments.kmer_size = 4;
    arguments.errors = 1;

    std::vector<size_t> const & window_span_begin{0, 4, 5};
    std::vector<size_t> const & window_span_end{11, 12, 13};

    valik::threshold threshold_data = valik::make_threshold_data(arguments);


    size_t const pattern_begin = 0; // |CGCAAAACGCGG|C pattern span [0,12)
    valik::pattern_bounds expected{};

    // minimisers [0; 2) = [0, 1]
    expected.first_index = 0;   // span for 0th minimiser [0, 11)
    expected.last_index = 2;    // span for 1st minimiser [4, 12)

    valik::pattern_bounds bounds = valik::make_pattern_bounds(pattern_begin, arguments, window_span_begin, window_span_end, threshold_data);

    EXPECT_EQ(bounds.first_index, expected.first_index);
    EXPECT_EQ(bounds.last_index, expected.last_index);
}

TEST(make_pattern_bounds, same_minimiser_consecutive_windows_begin)
{
    // special case where pattern starts after the first of multiple consecutive minimisers
    valik::search_arguments arguments{};
    arguments.pattern_size = 12;
    arguments.window_size = 8;
    arguments.kmer_size = 4;
    arguments.errors = 1;


    std::vector<size_t> const & window_span_begin{0, 4, 5};
    std::vector<size_t> const & window_span_end{11, 12, 13};

    valik::threshold threshold_data = valik::make_threshold_data(arguments);

    size_t const pattern_begin = 1; // C|GCAAAACGCGGC| pattern span [1,13)
    valik::pattern_bounds expected{};

    // minimisers [0; 3)
    expected.first_index = 0;   // span for 0th minimiser [0, 11)
    expected.last_index = 3;    // span for 2nd minimiser [5, 13)

    valik::pattern_bounds bounds = valik::make_pattern_bounds(pattern_begin, arguments, window_span_begin, window_span_end, threshold_data);

    EXPECT_EQ(bounds.first_index, expected.first_index);
    EXPECT_EQ(bounds.last_index, expected.last_index);
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
    std::vector<size_t> const & window_span_end{11, 12, 13};

    valik::threshold threshold_data = valik::make_threshold_data(arguments);

    size_t const pattern_begin = 1; // C|GCAAAACG|CGGC pattern span [1,9)
    valik::pattern_bounds expected{};

    // minimisers [0; 1)
    expected.first_index = 0;   // span for 0th minimiser [0, 11)
    expected.last_index = 1;

    valik::pattern_bounds bounds = valik::make_pattern_bounds(pattern_begin, arguments, window_span_begin, window_span_end, threshold_data);

    EXPECT_EQ(bounds.first_index, expected.first_index);
    EXPECT_EQ(bounds.last_index, expected.last_index);
}

//----------------------------------------------------------
//
// seq = CCACGTCGAAGGTT
// 	p = 12
// 	w = 8
// 	k = 4
//
// minimiser	             span
// ACGT		CCACGTCGAA       [0, 10)
// CGAA        CGTCGAAG      [3, 11)
// AAGG         GTCGAAGGT    [4, 13)
// aacc           CGAAGGTT   [6, 14)
//----------------------------------------------------------

TEST(make_pattern_bounds, same_minimiser_consecutive_windows_end)
{
    // special case where pattern ends after the first of multiple consecutive minimisers
    valik::search_arguments arguments{};
    arguments.pattern_size = 12;
    arguments.window_size = 8;
    arguments.kmer_size = 4;
    arguments.errors = 1;

    std::vector<size_t> const & window_span_begin{0, 3, 4, 6};
    std::vector<size_t> const & window_span_end{10, 11, 13, 14};

    valik::threshold threshold_data = valik::make_threshold_data(arguments);

    size_t const pattern_begin = 0; // |CCACGTCGAAGG|TT pattern span [0,12)
    valik::pattern_bounds expected{};

    // minimisers [0; 3)
    expected.first_index = 0;   // span for 0th minimiser [0, 10)
    expected.last_index = 3;    // span for 2nd minimiser [4, 13)

    valik::pattern_bounds bounds = valik::make_pattern_bounds(pattern_begin, arguments, window_span_begin, window_span_end, threshold_data);

    EXPECT_EQ(bounds.first_index, expected.first_index);
    EXPECT_EQ(bounds.last_index, expected.last_index);
}

//----------------------------------------------------------
// seq = CCACGTCGAAGGTT
// 	p = 12
// 	w = 8
// 	k = 4
//
// minimiser	             span
// ACGT		CCACGTCGA        [0, 9)
// CGAA        CGTCGAAG      [3, 11)
// AAGG          TCGAAGGT    [5, 13)
// aacc            GAAGGTT   [7, 14)
//----------------------------------------------------------

TEST(make_pattern_bounds, odd_lengths)
{
    // normal case where kmer size is not divisible by window or pattern size
    valik::search_arguments arguments{};
    arguments.pattern_size = 11;
    arguments.window_size = 7;
    arguments.kmer_size = 4;
    arguments.errors = 1;

    std::vector<size_t> const & window_span_begin{0, 3, 5, 7};
    std::vector<size_t> const & window_span_end{9, 11, 13, 14};

    valik::threshold threshold_data = valik::make_threshold_data(arguments);

    size_t const pattern_begin = 2; // CC|ACGTCGAAGGT|T pattern span [2,13)
    valik::pattern_bounds expected{};

    // minimisers [0; 3)
    expected.first_index = 0;   // span for 0th minimiser [0, 9)
    expected.last_index = 3;    // span for 2nd minimiser [5, 13)

    valik::pattern_bounds bounds = valik::make_pattern_bounds(pattern_begin, arguments, window_span_begin, window_span_end, threshold_data);

    EXPECT_EQ(bounds.first_index, expected.first_index);
    EXPECT_EQ(bounds.last_index, expected.last_index);
}
