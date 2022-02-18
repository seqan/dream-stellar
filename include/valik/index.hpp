// -----------------------------------------------------------------------------------------------------
// Copyright (c) 2006-2022, Knut Reinert & Freie Universität Berlin
// Copyright (c) 2016-2022, Knut Reinert & MPI für molekulare Genetik
// This file may be used, modified and/or redistributed under the terms of the 3-clause BSD-License
// shipped with this file and also available at: https://github.com/seqan/raptor/blob/master/LICENSE.md
// -----------------------------------------------------------------------------------------------------

#pragma once

#include <seqan3/argument_parser/exceptions.hpp>
#include <seqan3/search/dream_index/interleaved_bloom_filter.hpp>

#include <../lib/raptor/include/raptor/hierarchical_interleaved_bloom_filter.hpp>
#include <valik/shared.hpp>

namespace valik
{

namespace index_structure
{
    using ibf = seqan3::interleaved_bloom_filter<seqan3::data_layout::uncompressed>;
    using ibf_compressed = seqan3::interleaved_bloom_filter<seqan3::data_layout::compressed>;

    // TODO: add support for HIBF
    using hibf = raptor::hierarchical_interleaved_bloom_filter<seqan3::data_layout::uncompressed>;
    using hibf_compressed = raptor::hierarchical_interleaved_bloom_filter<seqan3::data_layout::compressed>;

    template <typename return_t, typename input_t>
    concept compressible_from =
        (std::same_as<return_t, ibf_compressed> && std::same_as<input_t, ibf>) ||
        (std::same_as<return_t, hibf_compressed> && std::same_as<input_t, hibf>);

} // namespace index_structure

template <typename data_t = index_structure::ibf>
class valik_index
{
private:
    template <typename friend_data_t>
    friend class valik_index;

    uint64_t window_size_{};
    seqan3::shape shape_{};
    bool compressed_{};
    std::vector<std::vector<std::string>> bin_path_{};
    data_t ibf_{};

public:
    static constexpr seqan3::data_layout data_layout_mode = data_t::data_layout_mode;
    static constexpr uint32_t version{1u};

    valik_index() = default;
    valik_index(valik_index const &) = default;
    valik_index(valik_index &&) = default;
    valik_index & operator=(valik_index const &) = default;
    valik_index & operator=(valik_index &&) = default;
    ~valik_index() = default;

    explicit valik_index(window const window_size,
                          seqan3::shape const shape,
                          bool const compressed,
                          std::vector<std::vector<std::string>> const & bin_path,
                          data_t && ibf)
    :
        window_size_{window_size.v},
        shape_{shape},
        compressed_{compressed},
        bin_path_{bin_path},
        ibf_{std::move(ibf)}
    {}

    explicit valik_index(build_arguments const & arguments) :
        window_size_{arguments.window_size},
        shape_{arguments.shape},
        compressed_{arguments.compressed},
        bin_path_{arguments.bin_path},
        ibf_{seqan3::bin_count{arguments.bins},
             seqan3::bin_size{arguments.bits},
             seqan3::hash_function_count{arguments.hash}}
    {
        static_assert(data_layout_mode == seqan3::data_layout::uncompressed);
    }

    template <typename other_data_t>
    explicit valik_index(valik_index<other_data_t> const & other)
    {
        static_assert(index_structure::compressible_from<data_t, other_data_t>);
        window_size_ = other.window_size_;
        shape_ = other.shape_;
        compressed_ = true;
        bin_path_ = other.bin_path_;
        ibf_ = data_t{other.ibf_};
    }

    template <typename other_data_t>
    explicit valik_index(valik_index<other_data_t> && other)
    {
        static_assert(index_structure::compressible_from<data_t, other_data_t>);
        window_size_ = std::move(other.window_size_);
        shape_ = std::move(other.shape_);
        compressed_ = true;
        bin_path_ = std::move(other.bin_path_);
        ibf_ = std::move(data_t{std::move(other.ibf_)});
    }

    uint64_t window_size() const
    {
        return window_size_;
    }

    seqan3::shape shape() const
    {
        return shape_;
    }

    bool compressed() const
    {
        return compressed_;
    }

    std::vector<std::vector<std::string>> const & bin_path() const
    {
        return bin_path_;
    }

    data_t & ibf()
    {
        return ibf_;
    }

    data_t const & ibf() const
    {
        return ibf_;
    }

    /*!\cond DEV
     * \brief Serialisation support function.
     * \tparam archive_t Type of `archive`; must satisfy seqan3::cereal_archive.
     * \param[in] archive The archive being serialised from/to.
     *
     * \attention These functions are never called directly, see \ref serialisation for more details.
     */
    template <seqan3::cereal_archive archive_t>
    void CEREAL_SERIALIZE_FUNCTION_NAME(archive_t & archive)
    {
        uint32_t parsed_version{valik_index<>::version};
        archive(parsed_version);
        if (parsed_version == valik_index<>::version)
        {
            try
            {
                archive(window_size_);
                archive(shape_);
                archive(compressed_);
                if ((data_layout_mode == seqan3::data_layout::compressed && !compressed_) ||
                    (data_layout_mode == seqan3::data_layout::uncompressed && compressed_))
                {
                    throw seqan3::argument_parser_error{"Data layouts of serialised and specified index differ."};
                }
                archive(bin_path_);
                archive(ibf_);
            }
            catch (std::exception const & e)
            {
                throw seqan3::argument_parser_error{"Cannot read index: " + std::string{e.what()}};
            }
        }
        else
        {
            throw seqan3::argument_parser_error{"Unsupported index version. Check raptor upgrade."}; // GCOVR_EXCL_LINE
        }
    }

    /* \brief Serialisation support function. Do not load the actual data.
     * \tparam archive_t Type of `archive`; must satisfy seqan3::cereal_input_archive.
     * \param[in] archive The archive being serialised from/to.
     * \param[in] version Index version.
     *
     * \attention These functions are never called directly, see \ref serialisation for more details.
     */
    template <seqan3::cereal_input_archive archive_t>
    void load_parameters(archive_t & archive)
    {
        uint32_t parsed_version{};
        archive(parsed_version);
        if (parsed_version == version)
        {
            try
            {
                archive(window_size_);
                archive(shape_);
                archive(compressed_);
                archive(bin_path_);
            }
// GCOVR_EXCL_START
            catch (std::exception const & e)
            {
                throw seqan3::argument_parser_error{"Cannot read index: " + std::string{e.what()}};
            }
// GCOVR_EXCL_STOP
        }
        else
        {
            throw seqan3::argument_parser_error{"Unsupported index version. Check valik upgrade."}; // GCOVR_EXCL_LINE
        }
    }
    //!\endcond

};

} // namespace valik
