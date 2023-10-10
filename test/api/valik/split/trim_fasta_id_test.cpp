#include <gtest/gtest.h>

#include <valik/split/metadata.hpp>

TEST(trim_fasta_id, no_whitespace)
{
    std::string id = "xy1";
    std::string expected = id;

    valik::trim_fasta_id(id);
    EXPECT_EQ(id, expected);
}

TEST(trim_fasta_id, only_whitespace)
{
    EXPECT_THROW({
        try
        {
            std::string id = "\n \t";
            valik::trim_fasta_id(id);
        }
        catch( const std::runtime_error& e )
        {
            // and this tests that it has the correct message
            EXPECT_STREQ( "Sequence name can not be empty.", e.what() );
            throw;
        }
    }, std::runtime_error );
}

TEST(trim_fasta_id, remove_whitespace)
{
    std::string id = " \txy1 \n";
    std::string expected = "xy1";

    valik::trim_fasta_id(id);
    EXPECT_EQ(id, expected);
}
