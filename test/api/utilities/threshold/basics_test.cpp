#include <gtest/gtest.h>

#include <utilities/threshold/basics.hpp>

TEST(factorial, manual_check)
{
    EXPECT_EQ(valik::factorial((uint64_t) 0), 1);
    EXPECT_EQ(valik::factorial((uint64_t) 1), 1);
    EXPECT_EQ(valik::factorial((uint64_t)7), 5040);
}

TEST(factorial, stirling_accuracy)
{
    double accuracy_bound = 0.05;   // allow 5% error
    std::vector<uint64_t> test_n{5, 10, 12, 17};

    for (auto n : test_n)
        EXPECT_TRUE(std::abs(1 - valik::exact_factorial(n) / (double) valik::stirling_factorial(n)) < accuracy_bound);
}

TEST(kmer_occurrences, small)
{
    uint8_t kmer_size = 4;
    uint64_t genome_len = 256 + kmer_size - 1;
    EXPECT_EQ(valik::expected_kmer_occurrences(genome_len, kmer_size), 1.0);
}

TEST(kmer_occurrences, human_genome)
{
    uint64_t human_genome_len = 3e9;
    uint8_t kmer_size = 16;
    EXPECT_LE(valik::expected_kmer_occurrences(human_genome_len, kmer_size), 1.0);
}

TEST(kmer_lemma, manual_test)
{
    size_t l = 100;
    uint8_t k = 10;

    uint8_t shared_kmer_count = l - k + 1; // 91
    for (uint8_t e{0}; e < 9; e++)
        EXPECT_EQ(valik::kmer_lemma_threshold(l, k, e), shared_kmer_count - k * e);

    uint8_t e = 10;
    EXPECT_EQ(valik::kmer_lemma_threshold(l, k, e), 0);

    l = 15;
    EXPECT_EQ(valik::kmer_lemma_threshold(l, k, e), 0);
}

TEST(combinations, edge_cases)
{
    uint8_t k = 3;
    size_t n = 3;
    EXPECT_EQ((valik::combinations<uint8_t, uint64_t>(k, n)), 1);

    k = 4;
    EXPECT_EQ((valik::combinations<uint8_t, uint64_t>(k, n)), 0);

    k = 0;
    n = 0;
    EXPECT_EQ((valik::combinations<uint8_t, uint64_t>(k, n)), 1);
}

TEST(combinations, manual_test)
{
    uint8_t k = 3;
    size_t n = 4;
    EXPECT_EQ((valik::combinations<uint8_t, uint64_t>(k, n)), 4);
    EXPECT_EQ((valik::combinations<uint8_t, uint64_t>(k, n)), (valik::combinations<uint8_t, uint64_t>(n - k, n)));

    n = 5;
    EXPECT_EQ((valik::combinations<uint8_t, uint64_t>(k, n)), 10);
    EXPECT_EQ((valik::combinations<uint8_t, uint64_t>(k, n)), (valik::combinations<uint8_t, uint64_t>(n - k, n)));
}
