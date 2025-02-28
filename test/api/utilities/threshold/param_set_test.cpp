#include <gtest/gtest.h>

#include <utilities/threshold/param_set.hpp>

TEST(ungapped_error_handling, kmer_size)
{
    valik::param_space space;
    uint8_t thresh = 5;
    uint8_t kmer_size = 6;
    EXPECT_THROW({
        try
        {
            valik::param_set(kmer_size, thresh, space);
        }
        catch( const std::runtime_error& e )
        {
            EXPECT_STREQ( ("k=" + std::to_string(kmer_size) + " out of range [7, 23]").c_str(), e.what() );
            throw;
        }
    }, std::runtime_error );

    kmer_size = 8;
    EXPECT_NO_THROW({
        valik::param_set(kmer_size, thresh, space);
    });

    kmer_size = 36;
    EXPECT_THROW({
        try
        {
            valik::param_set(kmer_size, thresh, space);
        }
        catch( const std::runtime_error& e )
        {
            EXPECT_STREQ( ("k=" + std::to_string(kmer_size) + " out of range [7, 23]").c_str(), e.what() );
            throw;
        }
    }, std::runtime_error );
}

TEST(gapped_error_handling, kmer_size)
{
    valik::param_space space;
    uint8_t thresh = 5;
    seqan3::shape s{seqan3::bin_literal{0b110101011}};
    utilities::kmer shaped_kmer{s};
    
    EXPECT_THROW({
        try
        {
            valik::param_set(shaped_kmer, thresh, space);
        }
        catch( const std::runtime_error& e )
        {
            EXPECT_STREQ( ("k=" + std::to_string(shaped_kmer.weight()) + " out of range [7, 23]").c_str(), e.what() );
            throw;
        }
    }, std::runtime_error );

    shaped_kmer = seqan3::shape{seqan3::bin_literal{0b1101010111}};
    EXPECT_NO_THROW({
        valik::param_set(shaped_kmer, thresh, space);
    });

    shaped_kmer = seqan3::shape{seqan3::bin_literal{0b111000000001010000000001111}};
    EXPECT_NO_THROW({
        valik::param_set(shaped_kmer, thresh, space);
    });

    shaped_kmer = seqan3::shape{seqan3::bin_literal{0b1111111100011110111100011111111}};
    EXPECT_THROW({
        try
        {
            valik::param_set(shaped_kmer, thresh, space);
        }
        catch( const std::runtime_error& e )
        {
            EXPECT_STREQ( ("k=" + std::to_string(shaped_kmer.weight()) + " out of range [7, 23]").c_str(), e.what() );
            throw;
        }
    }, std::runtime_error );
}
