#include <seqan3/std/ranges>     // range comparisons
#include <string>                // strings
#include <vector>                // vectors

#include <seqan3/test/snippet/create_temporary_snippet_file.hpp>

seqan3::test::create_temporary_snippet_file tmp_ibf_file{"tmp.ibf", "\nsome_content"};
seqan3::test::create_temporary_snippet_file dummy_sequence_file{"dummy.fasta", "\nACGTC"};
seqan3::test::create_temporary_snippet_file tmp_bin_list_file{"all_bins.txt", std::string{"\n"} + dummy_sequence_file.file_path.string()};

#include "cli_test.hpp"

TEST_F(valik, no_options)
{
    cli_test_result const result = execute_app("valik");
    std::string const expected
    {
        "valik - Pre-filter for querying databases of nucleotide sequences for approximate local matches.\n"
        "================================================================================================\n"
        "    Try -h or --help for more information.\n"
    };
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.out, expected);
    EXPECT_EQ(result.err, std::string{});
}

TEST_F(valik_split, no_options)
{
    cli_test_result const result = execute_app("valik", "split");
    std::string const expected
    {
        "valik - Pre-filter for querying databases of nucleotide sequences for approximate local matches.\n"
	"=========================================================================================================\n"
	"    Try -h or --help for more information.\n"
    };
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.out, expected);
    EXPECT_EQ(result.err, std::string{});
}

TEST_F(valik_build, no_options)
{
    cli_test_result const result = execute_app("valik", "build");
    std::string const expected
    {
        "valik - Pre-filter for querying databases of nucleotide sequences for approximate local matches.\n"
        "================================================================================================\n"
        "    Try -h or --help for more information.\n"
    };
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.out, expected);
    EXPECT_EQ(result.err, std::string{});
}

TEST_F(valik_search, no_options)
{
    cli_test_result const result = execute_app("valik", "search");
    std::string const expected
    {
        "valik - Pre-filter for querying databases of nucleotide sequences for approximate local matches.\n"
        "================================================================================================\n"
        "    Try -h or --help for more information.\n"
    };
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.out, expected);
    EXPECT_EQ(result.err, std::string{});
}

TEST_F(valik, no_subparser)
{
    cli_test_result const result = execute_app("valik", "foo");
    std::string const expected
    {
        "[Error] You either forgot or misspelled the subcommand! Please specify which sub-program you want to use: one "
        "of [split,build,search]. Use -h/--help for more information.\n"
    };
    EXPECT_NE(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, expected);
}

TEST_F(valik, unknown_option)
{
    cli_test_result const result = execute_app("valik", "-v");
    std::string const expected
    {
        "[Error] You either forgot or misspelled the subcommand! Please specify which sub-program you want to use: one "
        "of [split,build,search]. Use -h/--help for more information.\n"
    };
    EXPECT_NE(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, expected);
}

TEST_F(valik_split, input_missing)
{
    cli_test_result const result = execute_app("valik", "split",
                                                         "--segment-output seg",
                                                         "--reference-output ref");
    EXPECT_NE(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] Not enough positional arguments provided (Need at least 1). See -h/--help for more information.\n"});
}

TEST_F(valik_split, input_invalid)
{
    cli_test_result const result = execute_app("valik", "split",
                                                         "nonexistent",
                                                         "--segment-output seg",
                                                         "--reference-output ref");
    EXPECT_NE(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] Validation failed for positional option 1: The file \"nonexistent\" does not exist!\n"});
}

TEST_F(valik_split, too_short)
{
    cli_test_result const result = execute_app("valik", "split",
                                                         data("bin_0.fasta"),
                                                         "--segment-output seg",
                                                         "--reference-output ref",
                                                         "--length 0",
                                                         "--overlap 0");
    EXPECT_NE(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] The overlap size has to be smaller than the segment length.\n"});
}

TEST_F(valik_split, too_long)
{
    cli_test_result const result = execute_app("valik", "split",
                                                         data("bin_1.fasta"),
                                                         "--segment-output seg",
                                                         "--reference-output ref",
                                                         "--length 1000000");
    EXPECT_NE(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] The segment length is greater than the total length of the reference.\n"});
}

TEST_F(valik_split, no_bins)
{
    cli_test_result const result = execute_app("valik", "split",
                                                         "dummy.fasta",
                                                         "--segment-output seg",
                                                         "--reference-output ref",
                                                         "--bins 0");
    EXPECT_NE(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] Validation failed for option --bins: Value 0 is not in range [1,30000].\n"});
}

TEST_F(valik_build, input_missing)
{
    cli_test_result const result = execute_app("valik", "build",
                                                         "--size 8m",
                                                         "--output ./ibf.out");
    EXPECT_NE(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] Not enough positional arguments provided (Need at least 1). See -h/--help for more information.\n"});
}

TEST_F(valik_build, input_invalid)
{
    cli_test_result const result = execute_app("valik", "build",
                                                         "--size 8m",
                                                         "--output ./ibf.out",
                                                         "nonexistent");
    EXPECT_NE(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] Validation failed for positional option 1: The file \"nonexistent\" does not exist!\n"});
}

TEST_F(valik_build, output_missing)
{
    cli_test_result const result = execute_app("valik", "build",
                                                         "--size 8m",
                                                         tmp_bin_list_file.file_path);
    EXPECT_NE(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] Option --output is required but not set.\n"});
}

TEST_F(valik_build, output_wrong)
{
    cli_test_result const result = execute_app("valik", "build",
                                                         "--size 8m",
                                                         "--output foo/out.ibf",
                                                         tmp_bin_list_file.file_path);
    EXPECT_NE(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] Cannot write \"foo/out.ibf\"!\n"});
}

TEST_F(valik_build, size_missing)
{
    cli_test_result const result = execute_app("valik", "build",
                                                         "--output ./ibf.out",
                                                         tmp_bin_list_file.file_path);
    EXPECT_NE(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] Option --size is required but not set.\n"});
}

TEST_F(valik_build, size_wrong_space)
{
    cli_test_result const result = execute_app("valik", "build",
                                                         "--size 8 m",
                                                         "--output ./ibf.out",
                                                         tmp_bin_list_file.file_path);
    EXPECT_NE(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] Validation failed for option --size: Value 8 must be an integer "
                                      "followed by [k,m,g,t] (case insensitive).\n"});
}

TEST_F(valik_build, size_wrong_suffix)
{
    cli_test_result const result = execute_app("valik", "build",
                                                         "--size 8x",
                                                         "--output ibf.out",
                                                         tmp_bin_list_file.file_path);
    EXPECT_NE(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] Validation failed for option --size: Value 8x must be an integer "
                                      "followed by [k,m,g,t] (case insensitive).\n"});
}

TEST_F(valik_build, kmer_window)
{
    cli_test_result const result = execute_app("valik", "build",
                                                         "--kmer 20",
                                                         "--window 19",
                                                         "--size 8m",
                                                         "--output ibf.out",
                                                         tmp_bin_list_file.file_path);
    EXPECT_NE(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] The k-mer size cannot be bigger than the window size.\n"});
}

TEST_F(valik_search, ibf_missing)
{
    cli_test_result const result = execute_app("valik", "search",
                                                         "--query ", data("query.fq"),
                                                         "--output search.out");
    EXPECT_NE(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] Option --index is required but not set.\n"});
}

TEST_F(valik_search, ibf_wrong)
{
    cli_test_result const result = execute_app("valik", "search",
                                                         "--query ", data("query.fq"),
                                                         "--index foo.ibf",
                                                         "--output search.out");
    EXPECT_NE(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] Validation failed for option --index: The file \"foo.ibf\" does not "
                                      "exist!\n"});
}

TEST_F(valik_search, query_missing)
{
    cli_test_result const result = execute_app("valik", "search",
                                                         "--index ", tmp_ibf_file.file_path,
                                                         "--output search.out");
    EXPECT_NE(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] Option --query is required but not set.\n"});
}

TEST_F(valik_search, query_wrong)
{
    cli_test_result const result = execute_app("valik", "search",
                                                         "--query foo.fasta",
                                                         "--index ", tmp_ibf_file.file_path,
                                                         "--output search.out");
    EXPECT_NE(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] Validation failed for option --query: The file \"foo.fasta\" does not "
                                      "exist!\n"});
}

TEST_F(valik_search, output_missing)
{
    cli_test_result const result = execute_app("valik", "search",
                                                         "--query ", data("query.fq"),
                                                         "--index ", tmp_ibf_file.file_path);
    EXPECT_NE(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] Option --output is required but not set.\n"});
}

TEST_F(valik_search, output_wrong)
{
    cli_test_result const result = execute_app("valik", "search",
                                                         "--query ", data("query.fq"),
                                                         "--index ", tmp_ibf_file.file_path,
                                                         "--output foo/search.out");
    EXPECT_NE(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] Validation failed for option --output: Cannot write "
                                      "\"foo/search.out\"!\n"});
}

TEST_F(valik_search, pattern_window)
{
    cli_test_result const result = execute_app("valik", "search",
                                                         "--query ", data("query.fq"),
                                                         "--index ", tmp_ibf_file.file_path,
                                                         "--output search.out",
							                             "--pattern 12");
    EXPECT_NE(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] The minimiser window cannot be bigger than the pattern size.\n"});
}


