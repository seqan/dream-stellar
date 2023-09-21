#include <filesystem>
#include <fstream>
#include <ranges>     // range comparisons
#include <string>                // strings
#include <vector>                // vectors

#include "cli_test.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////// valik split equal length ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST_P(valik_split_various, split_various_lengths)
{
    auto const [seg_count, overlap] = GetParam();

    cli_test_result const result = execute_app("valik", "split",
                                                         data("various_chromosome_lengths.fasta"),
                                                         "--out reference_metadata.txt",
                                                         "--seg-count ", std::to_string(seg_count),
                                                         "--overlap ", std::to_string(overlap));

    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"Sequence: chr5 is too short and will be skipped.\n"});
    std::string const expected_segments = string_from_file(segment_metadata_path(overlap, seg_count), std::ios::binary);
    std::string const actual_segments = string_from_file("reference_metadata.txt", std::ios::binary);
    EXPECT_TRUE(expected_segments == actual_segments);
}


INSTANTIATE_TEST_SUITE_P(split_suite,
                         valik_split_various,
                         testing::Combine(testing::Values(4, 16), testing::Values(0, 20)),
                         [] (testing::TestParamInfo<valik_split_various::ParamType> const & info)
                         {
                             std::string name = std::to_string(std::get<0>(info.param)) + "_seg_count_" +
                                                std::to_string(std::get<1>(info.param)) + "_overlap";
                             return name;
                         });

TEST_P(valik_split_short, split_many_short)
{
    auto const [seg_count, overlap] = GetParam();

    cli_test_result const result = execute_app("valik", "split",
                                                        data("query.fastq"),
                                                        "--out query_metadata.txt",
                                                        "--seg-count ", std::to_string(seg_count),
                                                        "--overlap ", std::to_string(overlap));

    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});

    size_t read_count = 30;
    if (seg_count % 30 == 0)
    {
        EXPECT_EQ(result.err, std::string{});
    }
    // it is not advantageous to split 30 sequences of equal length into e.g 39 segments
    else
    {
        const std::string expected = "WARNING: Database was split into " +
                                     std::to_string((size_t) std::round((float) seg_count / read_count) * read_count) +
                                     " instead of " + std::to_string(seg_count) + " segments.";
        EXPECT_EQ(result.err, expected);
    }

    valik::metadata meta("query_metadata.txt");
    EXPECT_GE(0.1f, meta.segment_length_cv());  // create segments of roughly equal length
}

INSTANTIATE_TEST_SUITE_P(split_many_short_suite,
                         valik_split_short,
                         testing::Combine(testing::Values(31, 39, 41, 49, 51, 55, 60, 61, 71), testing::Values(0, 1, 9)),
                         [] (testing::TestParamInfo<valik_split_short::ParamType> const & info)
                         {
                             std::string name = std::to_string(std::get<0>(info.param)) + "_seg_count_" +
                                                std::to_string(std::get<1>(info.param)) + "_overlap";
                             return name;
                         });

TEST_P(valik_split_long, split_few_long)
{
    auto const [seg_count, overlap] = GetParam();

    cli_test_result const result = execute_app("valik", "split",
                                                        data("ref.fasta"),
                                                        "--out reference_metadata.txt",
                                                        "--seg-count ", std::to_string(seg_count),
                                                        "--overlap ", std::to_string(overlap));

    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{});


    valik::metadata meta("reference_metadata.txt");
    if (seg_count == meta.seq_count)
        EXPECT_EQ(meta.seq_count, meta.seg_count);  // one-to-one pairing of sequences and segments
    else
        EXPECT_GE(0.1f, meta.segment_length_cv());  // create segments of roughly equal length
}

INSTANTIATE_TEST_SUITE_P(split_few_long_suite,
                         valik_split_long,
                         testing::Combine(testing::Values(3, 12, 19), testing::Values(0, 1, 9)),
                         [] (testing::TestParamInfo<valik_split_long::ParamType> const & info)
                         {
                             std::string name = std::to_string(std::get<0>(info.param)) + "_seg_count_" +
                                                std::to_string(std::get<1>(info.param)) + "_overlap";
                             return name;
                         });

struct split_options : public valik_base {};

TEST_F(split_options, too_few_segments)
{
    size_t n = 29;
    size_t o = 0;
    cli_test_result const result = execute_app("valik", "split", data("query.fastq"), "--seg-count",
                                               std::to_string(n), "--overlap", std::to_string(o),
                                               "--out", "meta.txt");
    std::string const expected
    {
        "[Error] Can not split 30 sequences into " + std::to_string(n) + " segments.\n"
    };

    EXPECT_NE(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, expected);
}

TEST_F(split_options, overlap_too_large)
{
    size_t n = 30;
    size_t o = 2000;
    cli_test_result const result = execute_app("valik", "split", data("query.fastq"), "--seg-count",
                                               std::to_string(n), "--overlap", std::to_string(o),
                                               "--out", "meta.txt");
    EXPECT_NE(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    std::string err_first_half = result.err.substr(0, result.err.find("length") + 6);
    std::string err_second_half = result.err.substr(result.err.find("bp") + 2, result.err.size() - 1);
    EXPECT_EQ(err_first_half, std::string{"[Error] Segments of length"});
    std::string expected = " can not overlap by " + std::to_string(o) + "bp.\nDecrease the overlap or the number of segments.\n";
    EXPECT_EQ(err_second_half, expected);
}

TEST_F(split_options, too_many_segments)
{
    size_t n = 300;
    size_t o = 20;
    cli_test_result const result = execute_app("valik", "split", data("query.fastq"), "--seg-count",
                                               std::to_string(n), "--overlap", std::to_string(o),
                                               "--out", "meta.txt");
    EXPECT_NE(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    std::string err_first_half = result.err.substr(0, result.err.find("length") + 6);
    std::string err_second_half = result.err.substr(result.err.find("bp") + 2, result.err.size() - 1);
    EXPECT_EQ(err_first_half, std::string{"[Error] Segments of length"});
    std::string expected = " can not overlap by " + std::to_string(o) + "bp.\nDecrease the overlap or the number of segments.\n";
    EXPECT_EQ(err_second_half, expected);
}

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
    auto const [overlap, number_of_bins, window_size] = GetParam();

    std::string seg_input = cli_test::data("single_reference.fasta");
    std::string ref_meta_path = cli_test::data(std::to_string(overlap) + "overlap" + std::to_string(number_of_bins) + "bins.txt");

    //!TODO: the paths in the index are not data(path.fasta) so the file can't be opened by stellar (only a testing issue)
    cli_test_result const result = execute_app("valik", "build",
                                                         "--kmer 13",
                                                         "--window ", std::to_string(window_size),
                                                         "--size 32k",
                                                         "--output index.ibf",
                                                         "--ref-meta", ref_meta_path,
                                                         seg_input);
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{});

    compare_index(ibf_path(overlap, number_of_bins, window_size), "index.ibf");
}


INSTANTIATE_TEST_SUITE_P(segment_build_suite,
                         valik_build_segments,
                         testing::Combine(testing::Values(150), testing::Values(4, 16), testing::Values(15, 13)),
                         [] (testing::TestParamInfo<valik_build_segments::ParamType> const & info)
                         {
                             std::string name = std::to_string(std::get<0>(info.param)) + "_overlap_" +
                                                std::to_string(std::get<1>(info.param)) + "_bins_" +
                                                std::to_string(std::get<2>(info.param)) + "_window";
                             return name;
                         });

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////// valik search clusters ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST_P(valik_search_clusters, search)
{
    auto const [number_of_bins, window_size, number_of_errors, pattern_size, overlap] = GetParam();
    float error_rate = (float) number_of_errors / (float) pattern_size;

    setup_tmp_dir();
    setenv("VALIK_STELLAR", "echo", true);
    setenv("VALIK_MERGE", "echo", true);

    if (window_size == 23 && number_of_errors == 0)
        GTEST_SKIP() << "Needs dynamic threshold correction";

    cli_test_result const result = execute_app("valik", "search",
                                                        "--output search.gff",
                                                        "--distribute",
                                                        "--pattern", std::to_string(pattern_size),
                                                        "--overlap", std::to_string(overlap),
                                                        "--error-rate ", std::to_string(error_rate),
                                                        "--index ", ibf_path(number_of_bins, window_size),
                                                        "--query ", data("query.fq"),
                                                        "--threads 1",
                                                        "--tau 0.75",
                                                        "--p_max 0.75");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{});

    auto expected = string_list_from_file(search_result_path(number_of_bins, window_size, number_of_errors,
                pattern_size, overlap), std::ios::binary);
    auto actual = string_list_from_file("search.gff.out");

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
    float error_rate = (float) number_of_errors / (float) pattern_size;

    setup_tmp_dir();
    setenv("VALIK_STELLAR", "echo", true);
    setenv("VALIK_MERGE", "echo", true);

    cli_test_result const result = execute_app("valik", "search",
                                                        "--output search.gff",
                                                        "--distribute",
                                                        "--pattern", std::to_string(pattern_size),
                                                        "--overlap", std::to_string(overlap),
                                                        "--error-rate ", std::to_string(error_rate),
                                                        "--index ", ibf_path(segment_overlap, number_of_bins, window_size),
                                                        "--query ", data("single_query.fq"),
                                                        "--tau 0.75",
                                                        "--threads 1",
                                                        "--ref-meta", segment_metadata_path(segment_overlap, number_of_bins),
                                                        "--p_max 0.25");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{});

    auto expected = string_list_from_file(search_result_path(segment_overlap, number_of_bins, window_size, number_of_errors,
                pattern_size, overlap), std::ios::binary);
    auto actual = string_list_from_file("search.gff.out");

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
