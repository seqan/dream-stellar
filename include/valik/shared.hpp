#pragma once

#include <filesystem>
#include <vector>

#include <seqan3/io/sequence_file/input.hpp>
#include <seqan3/search/kmer_index/shape.hpp>

#include <raptor/threshold/threshold_parameters.hpp>

#include <stellar3.shared.hpp>

namespace valik
{

inline constexpr static uint64_t adjust_seed(uint8_t const kmer_size, uint64_t const seed = 0x8F3F73B5CF1C9ADEULL) noexcept
{
    return seed >> (64u - 2u * kmer_size);
}

//!\brief Strong type for passing the window size.
struct window { uint64_t v; };
//!\brief Strong type for passing the kmer size.
struct kmer { uint8_t v; };
//!\brief Strong type for passing number of bins.
struct bins { uint64_t v; };
//!\brief Strong type for passing number of bits.
struct bits { uint64_t v; };
//!\brief Strong type for passing number of hash functions.
struct hashes { uint64_t v; };

struct dna4_traits : seqan3::sequence_file_input_default_traits_dna
{
    using sequence_alphabet = seqan3::dna4;
};

struct split_arguments
{
    std::filesystem::path db_file{};
    std::filesystem::path db_out{"reference_metadata.txt"};
    std::filesystem::path seg_out{"reference_segments.txt"};

    size_t overlap{150};
    size_t seg_count{64};
    bool write_ref{false};
    bool write_query{false};
};

struct build_arguments
{
    uint32_t window_size{23u};
    uint8_t kmer_size{20};
    seqan3::shape shape{seqan3::ungapped{20u}};
    uint8_t shape_weight{shape.count()};
    uint8_t threads{1u};

    std::vector<std::vector<std::string>> bin_path{};
    std::filesystem::path bin_file{};
    std::filesystem::path out_path{"./"};
    std::string size{};
    uint64_t bins{64};
    uint64_t bits{4096};
    uint64_t hash{2};
    bool compressed{false};

    bool from_segments{false};
    std::filesystem::path seg_path{};
    std::filesystem::path ref_meta_path{};
};

struct minimiser_threshold_arguments
{
    virtual ~minimiser_threshold_arguments() = 0;   // make an abstract base struct

    double tau{0.9999};
    double threshold{std::numeric_limits<double>::quiet_NaN()};
    double p_max{0.15};
    double fpr{0.05};
    uint8_t errors{0};
    size_t pattern_size{};
    bool treshold_was_set{false};
    bool cache_thresholds{false};

    protected:
        // prevent creating, assigning or moving base struct instances
        minimiser_threshold_arguments() = default;
        minimiser_threshold_arguments(minimiser_threshold_arguments const&) = default;
        minimiser_threshold_arguments(minimiser_threshold_arguments&&) = default;
        minimiser_threshold_arguments& operator=(minimiser_threshold_arguments const&) = default;
        minimiser_threshold_arguments& operator=(minimiser_threshold_arguments&&) = default;
};

inline minimiser_threshold_arguments::~minimiser_threshold_arguments() = default;

struct search_arguments final : public minimiser_threshold_arguments, public stellar::StellarOptions
{
    ~search_arguments() override = default;
    search_arguments() = default;
    search_arguments(search_arguments const&) = default;
    search_arguments(search_arguments&&) = default;
    search_arguments& operator=(search_arguments const&) = default;
    search_arguments& operator=(search_arguments&&) = default;

    uint32_t window_size{23u};
    seqan3::shape shape{seqan3::ungapped{20u}};
    uint8_t shape_size{shape.size()};
    uint8_t shape_weight{shape.count()};
    uint64_t overlap{};

    uint8_t threads{1u};

    std::vector<std::vector<std::string>> bin_path{};
    std::filesystem::path query_file{};
    std::filesystem::path index_file{};
    std::filesystem::path out_file{"search.gff"};

    bool compressed{false};
    bool write_time{false};

    size_t cart_max_capacity{3}; //!TODO determine suitable values
    size_t max_queued_carts{10}; //!TODO determine suitable values

    raptor::threshold::threshold_parameters make_threshold_parameters() const noexcept
    {
        return
        {
            .window_size{window_size},
            .shape{shape},
            .pattern_size{pattern_size},
            .errors{errors},
            .percentage{threshold},
            .p_max{p_max},
            .fpr{fpr},
            .tau{tau},
            .cache_thresholds{cache_thresholds},
            .output_directory{index_file.parent_path()}
        };
    }

    std::filesystem::path seg_path{};
    std::filesystem::path ref_meta_path{};
    bool shared_memory{false};

};

} // namespace valik
