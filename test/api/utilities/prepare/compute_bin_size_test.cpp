#include <gtest/gtest.h>

#include "../../../app_test.hpp"

#include <utilities/prepare/compute_bin_size.hpp>
#include <valik/shared.hpp>
#include <valik/split/metadata.hpp>
#include <valik/split/write_seg_sequences.hpp>

struct compute_bin_size : public app_test
{};

TEST_F(compute_bin_size, split_db_no_count_cutoff)
{
    valik::build_arguments arguments{};
    arguments.bin_path = std::vector<std::string>{};
    arguments.kmer_count_min_cutoff = 0;
    arguments.kmer_count_max_cutoff = 254;
    size_t bin_count = 8;
    for (size_t b{0}; b < bin_count; b++)
        arguments.bin_path.emplace_back(data("ref_" + std::to_string(b) + ".fasta"));

    std::vector<seqan3::shape> shapes{seqan3::shape{seqan3::ungapped{8}}, seqan3::shape{seqan3::bin_literal{0b111110011111}}};
    for (auto shape : shapes)
    {
        arguments.shape = shape;
        arguments.window_size = shape.size() + 2;
        auto sequence_files_max_count = raptor::detail::kmer_count_from_sequence_files(arguments);
        std::vector<std::string> header_files{};
        for (size_t b{0}; b < bin_count; b++)
            header_files.emplace_back(data("s" + shape.to_string() + "_ref." + std::to_string(b) + ".minimiser"));

        auto minimiser_files_max_count = raptor::detail::kmer_count_from_minimiser_files(header_files, arguments.threads);
    
        EXPECT_EQ(sequence_files_max_count, minimiser_files_max_count);    
    }
}

TEST_F(compute_bin_size, segment_db_no_count_cutoff)
{
    size_t bin_count = 8;
    valik::build_arguments arguments{};
    arguments.bin_path = std::vector<std::string>{data("ref.fasta")};
    arguments.kmer_count_min_cutoff = 0;
    arguments.kmer_count_max_cutoff = 254;

    std::vector<seqan3::shape> shapes{seqan3::shape{seqan3::ungapped{8}}, seqan3::shape{seqan3::bin_literal{0b111110011111}}};
    for (auto shape : shapes)
    {
        arguments.ref_meta_path = data("s" + shape.to_string() + ".bin");
        arguments.shape = shape;
        arguments.window_size = shape.size() + 2;
        auto sequence_files_max_count = raptor::detail::kmer_count_from_sequence_files(arguments);
        std::vector<std::string> header_files{};
        for (size_t b{0}; b < bin_count; b++)
            header_files.emplace_back(data("s" + shape.to_string() + "_ref." + std::to_string(b) + ".minimiser"));

        auto minimiser_files_max_count = raptor::detail::kmer_count_from_minimiser_files(header_files, arguments.threads);
    
        EXPECT_EQ(sequence_files_max_count, minimiser_files_max_count);    
    }
}
