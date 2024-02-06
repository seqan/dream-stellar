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

TEST(kmer_attributes, basic_checks)
{
    valik::param_space space;

    std::vector<valik::kmer_attributes> attr_vec;
    if (!valik::read_fn_confs(attr_vec))
        valik::precalc_fn_confs(attr_vec);

    EXPECT_EQ(attr_vec.size(), std::get<1>(space.kmer_range) - std::get<0>(space.kmer_range) + 1);

    for (auto & attr : attr_vec)
    {
        EXPECT_EQ(attr.fn_conf_counts.size(), space.max_thresh);
        for (auto & thresh_table : attr.fn_conf_counts)
        {
            EXPECT_EQ(thresh_table.size(), space.max_errors + 1);
            for (auto & error_row : thresh_table)
            {
                EXPECT_EQ(error_row.size(), space.max_len + 1);
            }
        }
    }
}

// Test: case where there are no shared k-mers because the sequence length is less than the k-mer length
//       the conf count is equal to (l take e) because all possible error configuration destroy all shared k-mers
static void check_len_less_than_kmer_size(valik::kmer_attributes const & attr)
{
    for (auto & thresh_table : attr.fn_conf_counts)
    {
        for (size_t e{0}; e < thresh_table.size(); e++)
        {
            auto error_row = thresh_table[e];
            for (size_t l{0}; l < attr.k; l++)
            {
                EXPECT_EQ(error_row[l], (valik::combinations<size_t, uint64_t>(e, l)));
            }
        }
    }
}

// Test: case where the thresh parameter is less or equal to the k-mer lemma threshold
//       the conf count is 0 because no error configuration destroys more than the allowed number of k-mers
static void check_thresh_from_kmer_lemma(valik::kmer_attributes const & attr)
{
    for (uint8_t t{1}; t <= attr.fn_conf_counts.size(); t++)
    {
        auto thresh_table = attr.fn_conf_counts[t - 1];
        for (uint8_t e{0}; e < thresh_table.size(); e++)
        {
            auto error_row = thresh_table[e];
            for (size_t l{0}; l < error_row.size(); l++)
            {
                if (valik::kmer_lemma_threshold(l, attr.k, e) >= t)
                {
                    if (error_row[l] != 0)
                    {
                        std::cout << "l\t" << std::to_string(l) << '\n';
                        std::cout << "k\t" << std::to_string(attr.k) << '\n';
                        std::cout << "e\t" << std::to_string(e) << '\n';
                        std::cout << "t\t" << std::to_string(t) << '\n';
                    }
                    EXPECT_EQ(error_row[l], 0);
                }
            }
        }
    }
}

TEST(kmer_attributes, edge_cases)
{
    std::vector<valik::kmer_attributes> attr_vec;
    if (!valik::read_fn_confs(attr_vec))
        valik::precalc_fn_confs(attr_vec);

    /*
    size_t k = 9;
    size_t t = 5;
    size_t e = 15;
    size_t l = 148;

    // what it should be
    for (size_t i{1}; i <= k; i++)
        std::cout << std::to_string(attr_vec[k - 9].fn_conf_counts[t - 1][e - 1][l - i]) << '\n';
    
    std::cout << "extra\n";
    
    for (size_t j{1}; j < t; j++)
        std::cout << std::to_string(attr_vec[k - 9].fn_conf_counts[t - 1 - j][e - 1][l - k - j]) << '\n';

    std::cout << "------------------shortcut------------------\n";
    //row.push_back(row.back() + table.back()[l - 1]);
    std::cout << "+" << std::to_string(attr_vec[k - 9].fn_conf_counts[t - 1][e][l - 1]) << '\n';
    std::cout << "+" << std::to_string(attr_vec[k - 9].fn_conf_counts[t - 1][e - 1][l - 1]) << '\n';
    
    //row.back() -= table.back()[band + t - 1];
    std::cout << "-" << std::to_string(attr_vec[k - 9].fn_conf_counts[t - 1][e - 1][l - k - 1]) << '\n';
    
    for (uint8_t i = 1; i < t; i++)
    {
        //row.back() -= matrix[matrix.size() - i][e - 1][band + t - i - 1];
        std::cout << "-" << std::to_string(attr_vec[k - 9].fn_conf_counts[t - 1 - i][e - 1][l - k - i - 1]) << '\n';
    
        //row.back() += matrix[matrix.size() - i][e - 1][band + t - i];
        std::cout << "+" << std::to_string(attr_vec[k - 9].fn_conf_counts[t - 1 - i][e - 1][l - k - i]) << '\n';
    }
    */
    for (auto & attr : attr_vec)
    {
        check_len_less_than_kmer_size(attr);
        check_thresh_from_kmer_lemma(attr);
    }
}

TEST(kmer_attributes, exhaustive_comparison)
{
    std::vector<valik::kmer_attributes> attr_vec;
    if (!valik::read_fn_confs(attr_vec))
        valik::precalc_fn_confs(attr_vec);

    //e = 15; // why does this not work?    
    valik::param_space space;
    for (uint8_t k{std::get<0>(space.kmer_range)}; k <= std::get<1>(space.kmer_range); k++)
    {   
        auto kmer_attr = attr_vec[k - 9];
        for (size_t t{1}; t <= space.max_thresh; t++)
        {
            for (size_t e{1}; e <= space.max_errors; e++)
            {
                for (size_t l = k + t - 1; l <= space.max_len; l++)
                {
                    uint64_t calc_sum = attr_vec[k - 9].fn_conf_counts[t - 1][e][l];    
                    uint64_t proper_sum{0};
                    // what it should be
                    for (size_t i{1}; i <= k; i++)
                        proper_sum += attr_vec[k - 9].fn_conf_counts[t - 1][e - 1][l - i];

                    uint64_t row_sum = proper_sum;
        
                    for (size_t j{1}; j < t; j++)
                        proper_sum += attr_vec[k - 9].fn_conf_counts[t - 1 - j][e - 1][l - k - j];
    
                    if (calc_sum != proper_sum)
                    {
                        std::cout << "row_sum\tproper_sum\tcalc_sum\tk\tt\te\tl\n";
                        std::cout << row_sum << '\t' << proper_sum << '\t' << calc_sum << '\t' << std::to_string(k) << '\t' << t << '\t' << e << '\t' << l << '\n';
                    }
                    EXPECT_EQ(proper_sum, calc_sum);
                }
            }
        }
    }
}
