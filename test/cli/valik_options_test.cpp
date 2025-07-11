#include <ranges>     // range comparisons
#include <string>                // strings
#include <vector>                // vectors

#include <seqan3/test/snippet/create_temporary_snippet_file.hpp>

seqan3::test::create_temporary_snippet_file dummy_sequence_file{"dummy.fasta", "\n>chr\nACGTC"};
seqan3::test::create_temporary_snippet_file dummy_query_file{"query.fasta", "\n>id\nACGTC"};
seqan3::test::create_temporary_snippet_file tmp_bin_list_file{"all_bins.txt", std::string{"\n"} + dummy_sequence_file.file_path.string()};

#include "../app_test.hpp"

struct argparse : public app_test {};
struct argparse_build : public app_test {};
struct argparse_search : public app_test {};

TEST_F(argparse, no_options)
{
    app_test_result const result = execute_app("dream-stellar");
    std::string const expected
    {
	"dream-stellar - DNA search tool for finding local alignments between long sequences.\n"
	"====================================================================================\n"
    	"    Try -h or --help for more information.\n"
    };
    EXPECT_SUCCESS(result);
    EXPECT_EQ(result.out, expected);
    EXPECT_EQ(result.err, std::string{});
}

TEST_F(argparse_build, no_options)
{
    app_test_result const result = execute_app("dream-stellar", "build");
    std::string const expected
    {
	"dream-stellar - DNA search tool for finding local alignments between long sequences.\n"
	"====================================================================================\n"
    	"    Try -h or --help for more information.\n"
    };
    EXPECT_SUCCESS(result);
    EXPECT_EQ(result.out, expected);
    EXPECT_EQ(result.err, std::string{});
}

TEST_F(argparse_search, no_options)
{
    app_test_result const result = execute_app("dream-stellar", "search");
    std::string const expected
    {
	"dream-stellar - DNA search tool for finding local alignments between long sequences.\n"
	"====================================================================================\n"
    	"    Try -h or --help for more information.\n"
    };
    EXPECT_SUCCESS(result);
    EXPECT_EQ(result.out, expected);
    EXPECT_EQ(result.err, std::string{});
}

TEST_F(argparse, no_subparser)
{
    app_test_result const result = execute_app("dream-stellar", "foo");
    std::string const expected
    {
        "[Error] You specified an unknown subcommand! Available subcommands are: [build, search]. "
        "Use -h/--help for more information.\n"
    };
    EXPECT_FAILURE(result);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, expected);
}

TEST_F(argparse, unknown_option)
{
    app_test_result const result = execute_app("dream-stellar", "-v");
    std::string const expected
    {
        "[Error] Unknown option -v. In case this is meant to be a non-option/argument/parameter, "
        "please specify the start of non-options with '--'. See -h/--help for program information.\n"
    };
    EXPECT_FAILURE(result);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, expected);
}

TEST_F(argparse_build, input_missing)
{
    app_test_result const result = execute_app("dream-stellar", "build",
                                                         "--size 8m",
                                                         "--output ./ibf.out");
    EXPECT_FAILURE(result);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] Not enough positional arguments provided (Need at least 1). See -h/--help for more information.\n"});
}

TEST_F(argparse_build, input_invalid)
{
    app_test_result const result = execute_app("dream-stellar", "build",
                                                        "nonexistent",
                                                        "--size 8m",
                                                        "--output ./ibf.out");
    EXPECT_FAILURE(result);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] Validation failed for positional option 1: The file \"nonexistent\" does not exist!\n"});
}

TEST_F(argparse_build, output_wrong)
{
    app_test_result const result = execute_app("dream-stellar", "build",
                                                         dummy_sequence_file.file_path,
                                                         "--size 8m",
                                                         "--output foo/out.ibf");
    EXPECT_FAILURE(result);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] Cannot write \"foo/out.ibf\"!\n"});
}

TEST_F(argparse_build, size_wrong_space)
{
    app_test_result const result = execute_app("dream-stellar", "build",
                                                         dummy_sequence_file.file_path,
                                                         "--size 8 m",
                                                         "--output ./ibf.out");
    EXPECT_FAILURE(result);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] Validation failed for option --size: Value 8 must be an integer "
                                      "followed by [k,m,g,t] (case insensitive).\n"});
}

TEST_F(argparse_build, size_wrong_suffix)
{
    app_test_result const result = execute_app("dream-stellar", "build",
                                                         dummy_sequence_file.file_path,
                                                         "--size 8x",
                                                         "--output ibf.out");
    EXPECT_FAILURE(result);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] Validation failed for option --size: Value 8x must be an integer "
                                      "followed by [k,m,g,t] (case insensitive).\n"});
}

TEST_F(argparse_build, kmer_window)
{
    app_test_result const result = execute_app("dream-stellar", "build",
                                                         data("ref.fasta"),
                                                         "--kmer 20",
                                                         "--window 19",
                                                         "--size 8m",
                                                         "--output ibf.out", 
                                                         "--pattern 10",
                                                         "--seg-count 8",
                                                         "--without-parameter-tuning");
    EXPECT_FAILURE(result);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] The k-mer size cannot be bigger than the window size.\n"});
}

TEST_F(argparse_build, kmer_shape)
{
    app_test_result const result = execute_app("dream-stellar", "build",
                                                         dummy_sequence_file.file_path,
                                                         "--kmer 20",
                                                         "--shape 1100110011",
                                                         "--size 8m",
                                                         "--output ibf.out", 
                                                         "-n 8",
                                                         "--without-parameter-tuning");
    EXPECT_FAILURE(result);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] Arguments --kmer and --shape are mutually exclusive.\n"});
}

TEST_F(argparse_search, ibf_missing)
{
    app_test_result const result = execute_app("dream-stellar", "search",
                                                         "--query ", dummy_query_file.file_path,
                                                         "--output search.gff");
    EXPECT_FAILURE(result);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] Option --index is required but not set.\n"});
}

TEST_F(argparse_search, ibf_wrong)
{
    app_test_result const result = execute_app("dream-stellar", "search",
                                                         "--query ", dummy_query_file.file_path,
                                                         "--index foo.ibf",
                                                         "--output search.gff");
    EXPECT_FAILURE(result);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] Validation failed for option --index: The file \"foo.ibf\" does not "
                                      "exist!\n"});
}

TEST_F(argparse_search, query_missing)
{
    app_test_result const result = execute_app("dream-stellar", "search",
                                                         "--index ", data("8bins19window.ibf"),
                                                         "--output search.gff");
    EXPECT_FAILURE(result);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] Option --query is required but not set.\n"});
}

TEST_F(argparse_search, query_wrong)
{
    app_test_result const result = execute_app("dream-stellar", "search",
                                                         "--query foo.fasta",
                                                         "--index ", data("8bins19window.ibf"),
                                                         "--output search.gff");
    EXPECT_FAILURE(result);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] Validation failed for option --query: The file \"foo.fasta\" does not "
                                      "exist!\n"});
}

TEST_F(argparse_search, output_missing)
{
    app_test_result const result = execute_app("dream-stellar", "search",
                                                         "--query ", dummy_query_file.file_path,
                                                         "--index ", data("8bins19window.ibf"));
    EXPECT_FAILURE(result);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] Option --output is required but not set.\n"});
}

TEST_F(argparse_search, output_wrong)
{
    app_test_result const result = execute_app("dream-stellar", "search",
                                                         "--query ", dummy_query_file.file_path,
                                                         "--index ", data("8bins19window.ibf"),
                                                         "--output foo/search.gff");
    EXPECT_FAILURE(result);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] Validation failed for option --output: Cannot write \"foo/search.gff\"!\n"});
}

TEST_F(argparse_search, pattern_window)
{
    app_test_result const result = execute_app("dream-stellar", "search",
                                                         "--query ", dummy_query_file.file_path,
                                                         "--index ", data("8bins19window.ibf"),
                                                         "--output search.gff",
                                                         "--pattern 12",
                                                         "--without-parameter-tuning");
    EXPECT_FAILURE(result);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] The minimiser window cannot be bigger than the pattern.\n"});
}

TEST_F(argparse_search, incorrect_error_rate)
{
    app_test_result const result = execute_app("dream-stellar", "search",
                                                         "--query ", dummy_query_file.file_path,
                                                         "--index ", data("8bins19window.ibf"),
                                                         "--output search.gff",
                                                         "--error-rate 0.21");
    EXPECT_FAILURE(result);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, std::string{"[Error] Validation failed for option -e/--error-rate: Value 0.210000 is not in range [0.000000,0.200000].\n"});
}

TEST_F(argparse_search, no_meta_file)
{
    app_test_result const result = execute_app("dream-stellar", "search",
                                                        "--query ", dummy_query_file.file_path,
                                                        "--index ", data("index_copy_without_meta.ibf"),
                                                        "--output search.gff");
    EXPECT_FAILURE(result);
    EXPECT_EQ(result.out, std::string{});
    
    EXPECT_TRUE(result.err.find("[Error] The file") != std::string::npos);
    // do not specify metadata file path
    EXPECT_TRUE(result.err.find("does not exist!") != std::string::npos);
}
