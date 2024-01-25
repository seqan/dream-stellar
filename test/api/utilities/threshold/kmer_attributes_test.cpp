#include <gtest/gtest.h>

#include <filesystem>

#include <utilities/threshold/kmer_attributes.hpp>
#include <utilities/threshold/io.hpp>

#include <seqan3/test/expect_range_eq.hpp>
#include <seqan3/core/debug_stream.hpp>

// Generate the full path of a test input file that is provided in the data directory.
std::filesystem::path data_path(std::string const & filename)
{
    return std::filesystem::path{std::string{DATADIR}}.concat(filename);
}

TEST(kmer_attributes, equal_after_serialization)
{
    std::filesystem::remove(valik::fn_filename());
    std::vector<valik::kmer_attributes> precalc_attr_vec;
    valik::precalc_fn_confs(precalc_attr_vec);

    std::vector<valik::kmer_attributes> deserialized_attr_vec;
    valik::read_fn_confs(deserialized_attr_vec);
    EXPECT_EQ(precalc_attr_vec.size(), deserialized_attr_vec.size());
    for (size_t i{0}; i < precalc_attr_vec.size(); i++)
    {
        EXPECT_EQ(precalc_attr_vec[i].k, deserialized_attr_vec[i].k);
        EXPECT_EQ(precalc_attr_vec[i].fn_conf_counts.size(), deserialized_attr_vec[i].fn_conf_counts.size());
        for (size_t j{0}; j < precalc_attr_vec[i].fn_conf_counts.size(); j++)
        {
            EXPECT_EQ(precalc_attr_vec[i].fn_conf_counts[j].size(), deserialized_attr_vec[i].fn_conf_counts[j].size());
            for (size_t k{0}; k < precalc_attr_vec[i].fn_conf_counts[j].size(); k++)
            {
                EXPECT_RANGE_EQ(precalc_attr_vec[i].fn_conf_counts[j][k], deserialized_attr_vec[i].fn_conf_counts[j][k]);
            }
        }
    }
}
