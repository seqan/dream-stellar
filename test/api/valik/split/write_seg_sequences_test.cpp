#include <gtest/gtest.h>

#include "../../../app_test.hpp"

#include <valik/split/write_seg_sequences.hpp>

#include <seqan3/alphabet/nucleotide/dna4.hpp>
#include <seqan3/test/expect_range_eq.hpp>

struct write_sequences : public app_test
{
    static void trim_fasta_id(std::string & seg_seq)
    {
        size_t pos = seg_seq.find('\n');
        seg_seq = seg_seq.substr(pos);
        seg_seq.erase(std::remove_if(seg_seq.begin(),
                    seg_seq.end(),
                    [](unsigned char x){ return std::isspace(x); }),
                    seg_seq.end());
    }

    static void test_reference_out(size_t overlap, size_t bins)
    {
        std::string path_prefix = "write_out_" + std::to_string(overlap) + "_" + std::to_string(bins);

        valik::metadata meta(data(path_prefix + "_reference_metadata.bin"));
        valik::write_reference_segments(meta, data("database.fasta"));

        for (size_t i = 0; i < bins - 1; i++)
        {
            valik::metadata::segment_stats current_seg = meta.segment_from_bin(i);
            valik::metadata::segment_stats next_seg = meta.segment_from_bin(i + 1);
            
            std::string current_seg_seq = string_from_file(data("database_" + std::to_string(i) + ".fasta"), std::ios::binary);
            std::string next_seg_seq = string_from_file(data("database_" + std::to_string(i + 1) + ".fasta"), std::ios::binary);
            trim_fasta_id(current_seg_seq);
            trim_fasta_id(next_seg_seq);

            EXPECT_EQ(current_seg_seq.size(), current_seg.len);
            EXPECT_EQ(next_seg_seq.size(), next_seg.len);

            if (current_seg.seq_vec[0] == next_seg.seq_vec[0])
            {
                EXPECT_EQ(current_seg_seq.substr(current_seg_seq.size() - overlap), next_seg_seq.substr(0, overlap));
            }
        }
    }
    
    static void test_query_out(size_t overlap, size_t bins)
    {
        std::string path_prefix = "write_out_" + std::to_string(overlap) + "_" + std::to_string(bins);

        valik::metadata meta(data(path_prefix + "_reference_metadata.bin"));
        valik::write_query_segments(meta, data("database.fasta"));

        using sequence_file_t = seqan3::sequence_file_input<valik::dna4_traits, seqan3::fields<seqan3::field::seq>>;

        size_t i{0};
        seqan3::dna4_vector previous_seg_seq;
        for (auto && [current_seg_seq] : sequence_file_t{data("database.segments.fasta")})
        {
            if (i > 1)
            {
                valik::metadata::segment_stats previous_seg = meta.segment_from_bin(i - 1);
                valik::metadata::segment_stats current_seg = meta.segment_from_bin(i);

                EXPECT_EQ(previous_seg_seq.size(), previous_seg.len);
                EXPECT_EQ(current_seg_seq.size(), current_seg.len);

                if (previous_seg.seq_vec[0] == current_seg.seq_vec[0])
                {
                    EXPECT_RANGE_EQ(std::vector<seqan3::dna4>(previous_seg_seq.end() - overlap, previous_seg_seq.end()),
                                    std::vector<seqan3::dna4>(current_seg_seq.begin(), current_seg_seq.begin()+ overlap));
                }
            }

            i++;
            previous_seg_seq = current_seg_seq;
        }
    }
};

TEST_F(write_sequences, ref_o20_b4)
{
    size_t overlap = 20;
    size_t bins = 4;

    test_reference_out(overlap, bins);
}

TEST_F(write_sequences, ref_o20_b16)
{
    size_t overlap = 20;
    size_t bins = 16;

    test_reference_out(overlap, bins);
}

TEST_F(write_sequences, query_o20_b4)
{
    size_t overlap = 20;
    size_t bins = 4;

    test_query_out(overlap, bins);
}

TEST_F(write_sequences, query_o20_b16)
{
    size_t overlap = 20;
    size_t bins = 16;

    test_query_out(overlap, bins);
}
