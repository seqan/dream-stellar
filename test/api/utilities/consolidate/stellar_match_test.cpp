#include <gtest/gtest.h>

#include "../../../app_test.hpp"

#include <utilities/consolidate/stellar_match.hpp>

struct stellar_match : public app_test
{};

TEST_F(stellar_match, print_no_evalue)
{
    std::vector<std::string> match_vec{"chr1", "Stellar", "eps-matches", "10", "108", "0.987", "+", ".", "1;seq2Range=1280,1378;cigar=97M1D2M;mutations=14A,45G,58T,92C"};
    std::string expected = "chr1\tStellar\teps-matches\t10\t108\t0.987\t+\t.\t1;seq2Range=1280,1378;cigar=97M1D2M;mutations=14A,45G,58T,92C\n";
    valik::metadata meta(data("8bins50overlap_reference_metadata.bin"));
    auto match = valik::stellar_match(match_vec, meta);
    std::string match_str = match.to_string();
    EXPECT_EQ(match_str, expected);
}

TEST_F(stellar_match, print_full)
{
    std::vector<std::string> match_vec{"chr1", "Stellar", "eps-matches", "10", "108", "0.987", "+", ".", "1;seq2Range=1280,1378;eValue=4.05784e-73;cigar=97M1D2M;mutations=14A,45G,58T,92C"};
    std::string expected = "chr1\tStellar\teps-matches\t10\t108\t0.987\t+\t.\t1;seq2Range=1280,1378;eValue=4.05784e-73;cigar=97M1D2M;mutations=14A,45G,58T,92C\n";
    valik::metadata meta(data("8bins50overlap_reference_metadata.bin"));
    auto match = valik::stellar_match(match_vec, meta);
    std::string match_str = match.to_string();
    EXPECT_EQ(match_str, expected);
}

TEST_F(stellar_match, print_malformed)
{
    std::vector<std::string> match_vec{"chr1", "Stellar", "eps-matches", "10", "108", "0.987", "+", ".", "1;seq2Range=1280,1378;eValue=4.05784e-73"};
    std::string attributes = "1;seq2Range=1280,1378;eValue=4.05784e-73";
    valik::metadata meta(data("8bins50overlap_reference_metadata.bin"));
    EXPECT_THROW({
        try
        {
            auto match = valik::stellar_match(match_vec, meta);
        }
        catch( const std::runtime_error& e )
        {
            // and this tests that it has the correct message
            EXPECT_EQ( "Malformed GFF record:\n" + attributes, e.what() );
            throw;
        }
    }, std::runtime_error );
}
