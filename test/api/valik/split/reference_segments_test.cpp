#include <gtest/gtest.h>

#include <valik/split/reference_metadata.hpp>
#include <valik/split/reference_segments.hpp>

#include <random>

static void create_dummy_reference_metadata(size_t const seed, size_t const number_of_bins)
{
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> distr(10, 10000); // define the range

    std::ofstream file{"reference_metadata.txt"};
    for (size_t i{0}; i < number_of_bins; i++)
    {
        std::string sequence_stats = "chr" + std::to_string(i + 1) + "\t" + std::to_string(i) + "\t" + std::to_string(distr(gen));
        seqan3::debug_stream << sequence_stats << '\n';
        file << sequence_stats << '\n';
    }
    file << '\n';
}

static void print_segments(valik::reference_segments const & segments)
{
    seqan3::debug_stream << "Default len: " << segments.default_len << '\n';
    for (const auto & seg : segments.members)
    {
        seqan3::debug_stream << seg.bin << '\t' << seg.ref_ind << '\t' << seg.start << '\t' << seg.len << '\n';
    }
    seqan3::debug_stream << '\n';
}

TEST(reference_segments, o0_b4)
{
    size_t overlap = 0;
    size_t bins = 4;

    create_dummy_reference_metadata(42, bins);

    valik::reference_metadata reference("reference_metadata.txt", false);
    // Sort reference sequences by length
    std::sort (reference.sequences.begin(), reference.sequences.end());

    // For each segment assign start, length and bin number
    valik::reference_segments segments(bins, overlap, reference);
    print_segments(segments);
}

