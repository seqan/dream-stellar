#include <gtest/gtest.h>

#include <valik/split/metadata.hpp>
#include <utilities/threshold/find.hpp>
#include <utilities/threshold/fn_confs.hpp>

// Generate the full path of a test input file that is provided in the data directory.
std::filesystem::path data(std::string const & filename)
{
    return std::filesystem::path{std::string{DATADIR}}.concat(filename);
}

TEST(best_params, small)
{
    valik::param_space space{};
    valik::fn_confs fn_attr(space);
    
    valik::search_pattern pattern(4 /*e*/, 50 /*l*/);
    valik::metadata ref_meta(data("150overlap4bins.bin"));

    auto best_params = valik::get_best_params(pattern, ref_meta, fn_confs, true /*verbose*/);
    EXPECT_EQ(best_params.k, 10);
    EXPECT_EQ(best_params.t, 4); 
}


TEST(find_thresholds, small)
{
    valik::param_space space{};
    valik::fn_confs fn_attr(space);

    valik::metadata ref_meta(data("150overlap4bins.bin"));
    
    uint8_t kmer_size{11};
    auto kmer_attr = fn_confs.get_kmer_loss(kmer_size);
    
    uint8_t max_errors{15};

    auto profile = valik::find_thresholds_for_kmer_size(ref_meta, kmer_attr, max_errors);

    EXPECT_EQ(profile.k, kmer_size);
    EXPECT_EQ(profile.l, 150);
    EXPECT_EQ(profile.max_errors, max_errors);

    uint8_t err{15};
    auto error_profile = profile.get_error_profile(err);
    EXPECT_EQ(error_profile.params.k, kmer_size);
    EXPECT_EQ(error_profile.pattern.e, err);
    EXPECT_EQ(error_profile.pattern.l, 150);
     
    EXPECT_EQ(error_profile.search_type, valik::HEURISTIC);
    EXPECT_GE(error_profile.max_segment_len, 1500); // otherwise search_kind::STELLAR
    EXPECT_LE(error_profile.fnr, 0.1);
    EXPECT_LE(error_profile.fp_per_pattern, 0.1);
}

