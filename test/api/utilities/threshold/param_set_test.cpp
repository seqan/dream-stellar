#include <gtest/gtest.h>

#include <utilities/threshold/param_set.hpp>

TEST(error_handling, threshold)
{
    valik::param_space space;
    uint8_t kmer_size = 13;

    uint8_t thresh = 1;
    EXPECT_NO_THROW({
        valik::param_set(kmer_size, thresh, space);
    });

    thresh = 6;
    EXPECT_THROW({
        try
        {
            valik::param_set(kmer_size, thresh, space);
        }
        catch( const std::runtime_error& e )
        {
            EXPECT_STREQ( ("threshold=" + std::to_string(thresh) + " out of range [0, 5]").c_str(), e.what() );
            throw;
        }
    }, std::runtime_error );
}

TEST(error_handling, kmer_size)
{
    valik::param_space space;
    uint8_t thresh = 5;
    uint8_t kmer_size = 8;
    EXPECT_THROW({
        try
        {
            valik::param_set(kmer_size, thresh, space);
        }
        catch( const std::runtime_error& e )
        {
            EXPECT_STREQ( ("k=" + std::to_string(kmer_size) + " out of range [9, 21]").c_str(), e.what() );
            throw;
        }
    }, std::runtime_error );

    kmer_size = 9;
    EXPECT_NO_THROW({
        valik::param_set(kmer_size, thresh, space);
    });

    kmer_size = 22;
    EXPECT_THROW({
        try
        {
            valik::param_set(kmer_size, thresh, space);
        }
        catch( const std::runtime_error& e )
        {
            EXPECT_STREQ( ("k=" + std::to_string(kmer_size) + " out of range [9, 21]").c_str(), e.what() );
            throw;
        }
    }, std::runtime_error );
}
