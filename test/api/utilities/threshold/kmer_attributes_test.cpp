#include <gtest/gtest.h>

#include <utilities/threshold/kmer_attributes.hpp>

// Generate the full path of a test input file that is provided in the data directory.
std::filesystem::path data_path(std::string const & filename)
{
    return std::filesystem::path{std::string{DATADIR}}.concat(filename);
}

TEST(kmer_attributes, bins8overlap50)
{
    EXPECT_EQ(0, 0);    
}
