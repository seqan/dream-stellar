#include <gtest/gtest.h>

#include <valik/split/reference_metadata.hpp>
#include <valik/split/reference_segments.hpp>

#include <seqan3/test/snippet/create_temporary_snippet_file.hpp>
                                                                                            // ref_id   ref_len
seqan3::test::create_temporary_snippet_file reference_metadata_file{"reference_metadata.txt", "chr1\t102"
                                                                                              "chr2\t248"};


// if seg_len = 500 and seq.len = 1002 make two segments of length 501 not three where seg lengths (500, 500, 2)
TEST(reference_segments, normal)
{
    valik::reference_metadata reference("reference_metadata.txt", false);

    size_t seg_len = 50;
    size_t bins = 8;
    size_t overlap = 10;

    valik::reference_segments segments(seg_len, bins, overlap, reference);

    size_t expected = 350;

    EXPECT_EQ(reference.total_len, expected);
}