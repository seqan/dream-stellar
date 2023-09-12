#include <gtest/gtest.h>

#include <utilities/consolidate/consolidate_matches.hpp>

// Generate the full path of a test input file that is provided in the data directory.
std::filesystem::path data_path(std::string const & filename)
{
    return std::filesystem::path{std::string{DATADIR}}.concat(filename);
}

std::filesystem::path consolidation_input_path(size_t const number_of_bins, size_t const overlap) noexcept
{
    std::string name{};
    name += std::to_string(number_of_bins);
    name += "bins";
    name += std::to_string(overlap);
    name += "overlap_dream_all.gff";
    return data_path(name);
}

std::filesystem::path consolidation_meta_path(size_t const number_of_bins, size_t const overlap) noexcept
{
    std::string name{};
    name += std::to_string(number_of_bins);
    name += "bins";
    name += std::to_string(overlap);
    name += "overlap_reference_metadata.tsv";
    return data_path(name);
}

void compare_gff_out(std::vector<valik::stellar_match> const & expected,
                            std::vector<valik::stellar_match> const & actual)
{
    EXPECT_EQ(expected.size(), actual.size());
    size_t not_actually_found{0};
    for (auto & match : expected)
    {
        auto it = std::find(actual.begin(), actual.end(), match);
        if (it == actual.end())
        {
            not_actually_found++;
            seqan3::debug_stream << match.to_string();
        }

        // EXPECT_EQ(match.percid, (*it).percid);
        // EXPECT_EQ(match.attributes, (*it).attributes);
    }

    EXPECT_EQ(not_actually_found, 0);
}

TEST(consolidate_matches, bins8overlap50)
{
    size_t number_of_bins = 8;
    size_t segment_overlap = 50;

    valik::search_arguments arguments{};
    arguments.ref_meta_path = consolidation_meta_path(number_of_bins, segment_overlap);
    arguments.all_matches = consolidation_input_path(number_of_bins, segment_overlap);
    arguments.out_file = "consolidated.gff";

    valik::consolidate_matches(arguments);

    valik::database_metadata reference(arguments.ref_meta_path, false);
    auto expected = valik::read_stellar_output(data_path("stellar_truth.gff"), reference, std::ios::binary);
    auto actual = valik::read_stellar_output("consolidated.gff", reference, std::ios::binary);

    compare_gff_out(expected, actual);
}

TEST(consolidate_matches, bins16overlap50)
{
    size_t number_of_bins = 16;
    size_t segment_overlap = 50;

    valik::search_arguments arguments{};
    arguments.ref_meta_path = consolidation_meta_path(number_of_bins, segment_overlap);
    arguments.all_matches = consolidation_input_path(number_of_bins, segment_overlap);
    arguments.out_file = "consolidated.gff";

    valik::consolidate_matches(arguments);

    valik::database_metadata reference(arguments.ref_meta_path, false);
    auto expected = valik::read_stellar_output(data_path("stellar_truth.gff"), reference, std::ios::binary);
    auto actual = valik::read_stellar_output("consolidated.gff", reference, std::ios::binary);

    compare_gff_out(expected, actual);
}
