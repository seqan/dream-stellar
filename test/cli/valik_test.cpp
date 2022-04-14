#include <fstream>
#include <seqan3/std/ranges>     // range comparisons
#include <string>                // strings
#include <vector>                // vectors

#include "cli_test.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////// valik split tests ///////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST_P(valik_split, split)
{
    auto const [overlap, bins] = GetParam();

    cli_test_result const result = execute_app("valik", "split",
                                                         data("various_chromosome_lengths.fasta"),
                                                         "--overlap ", std::to_string(overlap),
                                                         "--bins ", std::to_string(bins),
                                                         "--reference-output reference_metadata.txt",
                                                         "--segment-output reference_segments.txt");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"Reference sequence: chr5 is too short and will be skipped.\n"});

    std::string const expected_metadata = string_from_file(data("chromosome_metadata.txt"), std::ios::binary);
    std::string const actual_metadata = string_from_file("reference_metadata.txt", std::ios::binary);

    EXPECT_TRUE(expected_metadata == actual_metadata);

    std::string const expected_segments = string_from_file(segment_metadata_path(overlap, bins), std::ios::binary);
    std::string const actual_segments = string_from_file("reference_segments.txt", std::ios::binary);

    EXPECT_TRUE(expected_segments == actual_segments);
}


INSTANTIATE_TEST_SUITE_P(split_suite,
                         valik_split,
                         testing::Combine(testing::Values(0, 20), testing::Values(4, 16)),
                         [] (testing::TestParamInfo<valik_split::ParamType> const & info)
                         {
                             std::string name = std::to_string(std::get<0>(info.param)) + "_overlap_" +
                                                std::to_string(std::get<1>(info.param)) + "_bins";
                             return name;
                         });

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////// valik build clusters /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST_P(valik_build_clusters, build_from_clusters)
{
    auto const [number_of_bins, window_size, run_parallel_tmp] = GetParam();
    bool const run_parallel = run_parallel_tmp && number_of_bins >= 32;

    {
        std::ofstream file{"bin_paths.txt"};
	for (size_t i{0}; i < number_of_bins; i++)
        {
	    std::string file_path = cli_test::data("bin_" + std::to_string(i) + ".fasta");
            file << file_path << '\n';
        }
        file << '\n';
    }

    cli_test_result const result = execute_app("valik", "build",
                                                         "--kmer 19",
                                                         "--window ", std::to_string(window_size),
                                                         "--size 32k",
                                                         "--threads ", run_parallel ? "2" : "1",
                                                         "--output index.ibf",
                                                         "bin_paths.txt");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{});

    compare_index(ibf_path(number_of_bins, window_size), "index.ibf");
}


INSTANTIATE_TEST_SUITE_P(cluster_build_suite,
                         valik_build_clusters,
                         testing::Combine(testing::Values(8), testing::Values(19, 23), testing::Values(true, false)),
                         [] (testing::TestParamInfo<valik_build_clusters::ParamType> const & info)
                         {
                             std::string name = std::to_string(std::get<0>(info.param)) + "_bins_" +
                                                std::to_string(std::get<1>(info.param)) + "_window_" +
                                                (std::get<2>(info.param) ? "parallel" : "serial");
                             return name;
                         });

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////// valik build segments /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST_P(valik_build_segments, build_from_segments)
{
    auto const [overlap, number_of_bins, window_size, run_parallel_tmp] = GetParam();
    bool const run_parallel = run_parallel_tmp && number_of_bins >= 32;

    std::string seg_input = cli_test::data("single_reference.fasta");
    std::string ref_meta_path = cli_test::data("reference_metadata.txt");
    std::string seg_meta_path = cli_test::data(std::to_string(overlap) + "overlap" + std::to_string(number_of_bins) + "bins.txt");

    cli_test_result const result = execute_app("valik", "build",
                                                         "--kmer 13",
                                                         "--window ", std::to_string(window_size),
                                                         "--size 100k",
                                                         "--threads ", run_parallel ? "2" : "1",
                                                         "--output index.ibf",
                                                         "--from-segments",
                                                         "--ref-meta", ref_meta_path,
                                                         "--seg-path", seg_meta_path,
                                                         seg_input);
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{});

    compare_index(ibf_path(overlap, number_of_bins, window_size), "index.ibf");
}


INSTANTIATE_TEST_SUITE_P(segment_build_suite,
                         valik_build_segments,
                         testing::Combine(testing::Values(150), testing::Values(4, 16), testing::Values(15, 13), testing::Values(true, false)),
                         [] (testing::TestParamInfo<valik_build_segments::ParamType> const & info)
                         {
                             std::string name = std::to_string(std::get<0>(info.param)) + "_overlap_" +
                                                std::to_string(std::get<1>(info.param)) + "_bins_" +
                                                std::to_string(std::get<2>(info.param)) + "_window_" +
                                                (std::get<3>(info.param) ? "parallel" : "serial");
                             return name;
                         });

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////// valik search clusters ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST_P(valik_search_clusters, search)
{
    auto const [number_of_bins, window_size, number_of_errors, pattern_size, overlap] = GetParam();

    if (window_size == 23 && number_of_errors == 0)
        GTEST_SKIP() << "Needs dynamic threshold correction";

    cli_test_result const result = execute_app("valik", "search",
                                                        "--output search.out",
                                                        "--pattern", std::to_string(pattern_size),
							                            "--overlap", std::to_string(overlap),
                                                        "--error ", std::to_string(number_of_errors),
                                                        "--index ", ibf_path(number_of_bins, window_size),
                                                        "--query ", data("query.fq"),
							                            "--tau 0.75",
							                            "--p_max 0.75");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{});

    std::string const expected = string_from_file(search_result_path(number_of_bins, window_size, number_of_errors,
			    pattern_size, overlap), std::ios::binary);
    std::string const actual = string_from_file("search.out");

    EXPECT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(cluster_search_suite,
                         valik_search_clusters,
                         testing::Combine(testing::Values(8), testing::Values(19, 23), testing::Values(0, 1),
				 testing::Values(50, 100), testing::Values(1, 40)),
                         [] (testing::TestParamInfo<valik_search_clusters::ParamType> const & info)
                         {
                             std::string name = std::to_string(std::get<0>(info.param)) + "_bins_" +
                                                std::to_string(std::get<1>(info.param)) + "_window_" +
                                                std::to_string(std::get<2>(info.param)) + "_error_" +
						                        std::to_string(std::get<3>(info.param)) + "_pattern_" +
						                        std::to_string(std::get<4>(info.param)) + "_overlap";
                             return name;
                         });

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////// valik search segments ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST_P(valik_search_segments, search)
{
    auto const [segment_overlap, number_of_bins, window_size, number_of_errors, pattern_size, overlap] = GetParam();

    if (window_size == 23 && number_of_errors == 0)
        GTEST_SKIP() << "Needs dynamic threshold correction";

    cli_test_result const result = execute_app("valik", "search",
                                                        "--output search.out",
                                                        "--pattern", std::to_string(pattern_size),
							                            "--overlap", std::to_string(overlap),
                                                        "--error ", std::to_string(number_of_errors),
                                                        "--index ", ibf_path(segment_overlap, number_of_bins, window_size),
                                                        "--query ", data("single_query.fq"),
							                            "--tau 0.75",
							                            "--p_max 0.75");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{});

    std::string const expected = string_from_file(search_result_path(segment_overlap, number_of_bins, window_size, number_of_errors,
			    pattern_size, overlap), std::ios::binary);
    std::string const actual = string_from_file("search.out");

    EXPECT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(segment_search_suite,
                         valik_search_segments,
                         testing::Combine(testing::Values(150), testing::Values(4, 16), testing::Values(15, 13), testing::Values(1),
                         testing::Values(50), testing::Values(49)),
                         [] (testing::TestParamInfo<valik_search_segments::ParamType> const & info)
                         {
                             std::string name = std::to_string(std::get<1>(info.param)) + "_bins_" +
                                                std::to_string(std::get<2>(info.param)) + "_window_" +
                                                std::to_string(std::get<3>(info.param)) + "_error_" +
						                        std::to_string(std::get<4>(info.param)) + "_pattern_" +
						                        std::to_string(std::get<5>(info.param)) + "_overlap";
                             return name;
                         });
