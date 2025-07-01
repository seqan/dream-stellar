// SPDX-FileCopyrightText: 2006-2025 Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2025 Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: CC0-1.0

#pragma once

#include <algorithm>
#include <vector>

#include "../app_test.hpp"

#include <seqan3/test/expect_range_eq.hpp>
#include <utilities/consolidate/stellar_match.hpp>
#include <valik/index.hpp>

struct app_test_cli_base : public app_test
{
    static std::vector<std::string> string_list_from_file(std::filesystem::path const & path, std::ios_base::openmode const mode = std::ios_base::in)
    {
        std::string file_str = string_from_file(path, mode);
        std::stringstream str(file_str);

        std::vector<std::string> line_vec;

        std::string tmp;
        while(std::getline(str, tmp, '\n'))
        {
            line_vec.push_back(tmp);
        }

        std::ranges::sort(line_vec);
        return line_vec;
    }

    static void setup_tmp_dir()
    {
        std::filesystem::path tmp_dir = "tmp/valik/my_dir";
        setenv("VALIK_TMP", tmp_dir.c_str(), true);

        std::filesystem::create_directories(tmp_dir);
    }
    
    static void compare_gff_out(std::vector<valik::stellar_match> const & expected,
                                std::vector<valik::stellar_match> const & actual)
    {
        EXPECT_EQ(expected.size(), actual.size());
        std::map<std::string, size_t> expected_match_counter{};
        for (auto & match : expected)
        {
            expected_match_counter[match.qname]++;
        }

        std::map<std::string, size_t> actual_match_counter{};
        for (auto & match : actual)
        {
            actual_match_counter[match.qname]++;
        }

        if (!actual_match_counter.empty() && !expected_match_counter.empty())
        {
            for (auto it = expected_match_counter.begin(); it != expected_match_counter.end(); it++)
            {
                EXPECT_EQ(actual_match_counter.at((*it).first), (*it).second);
            }
        }
    }
    
    static std::filesystem::path ibf_path(size_t const number_of_bins, size_t const window_size) noexcept
    {
        std::string name{};
        name += std::to_string(number_of_bins);
        name += "bins";
        name += std::to_string(window_size);
        name += "window.ibf";
        return data(name);
    }

    static std::filesystem::path ibf_path(size_t const overlap, size_t const number_of_bins, size_t const window_size) noexcept
    {
        std::string name{};
        name += std::to_string(overlap);
        name += "overlap";
        name += std::to_string(number_of_bins);
        name += "bins";
        name += std::to_string(window_size);
        name += "window.ibf";
        return data(name);
    }
    
    static std::filesystem::path search_result_path(size_t const number_of_bins, size_t const window_size, size_t const number_of_errors, 
                                                    size_t const pattern_size, size_t const query_every) noexcept
    {
        std::string name{};
        name += std::to_string(number_of_bins);
        name += "bins";
        name += std::to_string(window_size);
        name += "window";
        name += std::to_string(number_of_errors);
        name += "error";
        name += std::to_string(pattern_size);
        name += "pattern";
        name += std::to_string(query_every);
        name += "query_every";
        name += ".gff.out";
        return data(name);
    }

    static std::filesystem::path search_result_path(size_t const segment_overlap, size_t const number_of_bins, 
                                                    size_t const window_size, size_t const number_of_errors) noexcept
    {
        std::string name{};
        name += std::to_string(segment_overlap);
        name += "overlap";
        name += std::to_string(number_of_bins);
        name += "bins";
        name += std::to_string(window_size);
        name += "window";
        name += std::to_string(number_of_errors);
        name += "errors";
        name += ".gff.out";
        return data(name);
    }

    static std::filesystem::path search_result_path(size_t const number_of_errors) noexcept
    {
        std::string name;
        name += std::to_string(number_of_errors);
        name += "error";
        name += ".gff";
        return data(name);
    }
    
    struct strong_bool
    {
        enum
        {
            yes,
            no
        } value;

        strong_bool(decltype(value) v) : value(v) {}

        explicit operator bool() const
        {
            return value == strong_bool::yes;
        }

        bool operator!() const
        {
            return value == strong_bool::no;
        }
    };
    
    struct compare_extension : strong_bool
    {
        using strong_bool::value;
        using strong_bool::strong_bool;
    };
    
    // Good example for printing tables: https://en.cppreference.com/w/cpp/io/ios_base/width
    template <seqan3::data_layout layout = seqan3::data_layout::uncompressed>
    static std::string debug_ibfs(seqan3::interleaved_bloom_filter<layout> const & expected_ibf,
                                  seqan3::interleaved_bloom_filter<layout> const & actual_ibf)
    {
        std::stringstream result{};
        result << ">>>IBFs differ<<<\n";
        result.setf(std::ios::left, std::ios::adjustfield);

        result.width(22);
        result << "#Member accessor";
        result.width(15);
        result << "Expected value";
        result.width(13);
        result << "Actual value";
        result << '\n';

        result.width(22);
        result << "bin_count()";
        result.width(15);
        result << expected_ibf.bin_count();
        result.width(13);
        result << actual_ibf.bin_count();
        result << '\n';

        result.width(22);
        result << "bin_size()";
        result.width(15);
        result << expected_ibf.bin_size();
        result.width(13);
        result << actual_ibf.bin_size();
        result << '\n';

        result.width(22);
        result << "hash_function_count()";
        result.width(15);
        result << expected_ibf.hash_function_count();
        result.width(13);
        result << actual_ibf.hash_function_count();
        result << '\n';

        result.width(22);
        result << "bit_size()";
        result.width(15);
        result << expected_ibf.bit_size();
        result.width(13);
        result << actual_ibf.bit_size();
        result << '\n';

        return result.str();
    }
    
    template <typename data_t = valik::index_structure::ibf>
    static void compare_index(std::filesystem::path const & expected_result,
                                     std::filesystem::path const & actual_result,
                                     compare_extension const compare_ext = compare_extension::yes)
    {
        constexpr bool is_ibf = std::same_as<data_t, valik::index_structure::ibf>;
        static_assert(is_ibf);

        valik::valik_index<data_t> expected_index{}, actual_index{};

        {
            std::ifstream is{expected_result, std::ios::binary};
            cereal::BinaryInputArchive iarchive{is};
            iarchive(expected_index);
        }
        {
            std::ifstream is{actual_result, std::ios::binary};
            cereal::BinaryInputArchive iarchive{is};
            iarchive(actual_index);
        }

        EXPECT_EQ(expected_index.window_size(), actual_index.window_size());
        EXPECT_EQ(expected_index.shape(), actual_index.shape());

        if constexpr(is_ibf)
        {
            auto const & expected_ibf{expected_index.ibf()}, actual_ibf{actual_index.ibf()};
            EXPECT_TRUE(expected_ibf == actual_ibf) << debug_ibfs<data_t::data_layout_mode>(expected_ibf, actual_ibf);
        }
        else
        {
            auto const & expected_ibfs{expected_index.ibf().ibf_vector}, actual_ibfs{actual_index.ibf().ibf_vector};
            for (auto const & expected_ibf : expected_ibfs)
            {
                ASSERT_TRUE(std::ranges::find(actual_ibfs, expected_ibf) != actual_ibfs.end());
            }
        }

        auto const & all_expected_bins{expected_index.bin_path()}, all_actual_bins{actual_index.bin_path()};
        EXPECT_EQ(std::ranges::distance(all_expected_bins), std::ranges::distance(all_actual_bins));

        if constexpr(is_ibf)
        {
            for (auto const && [expected_file, actual_file] : seqan3::views::zip(all_expected_bins, all_actual_bins))
            {
                std::filesystem::path const expected_path(expected_file);
                std::filesystem::path const actual_path(actual_file);
                if (compare_ext)
                    ASSERT_EQ(expected_path.filename(), actual_path.filename());
                else
                    ASSERT_EQ(expected_path.stem(), actual_path.stem());
            }
        }
        else
        {
            auto filenames = std::views::transform([compare_ext] (std::vector<std::string> const & filename_list)
            {
                std::vector<std::string> result{};
                if (compare_ext)
                    for (auto const & filename : filename_list)
                        result.emplace_back(std::filesystem::path{filename}.filename().string());
                else
                    for (auto const & filename : filename_list)
                        result.emplace_back(std::filesystem::path{filename}.stem().string());
                return result;
            });

            auto expected_filenames_view = all_expected_bins | filenames;
            auto actual_filenames_view = all_actual_bins | filenames;

            std::vector<std::string> expected_filenames(expected_filenames_view.begin(),
                                                                     expected_filenames_view.end());
            std::vector<std::string> actual_filenames(actual_filenames_view.begin(),
                                                                   actual_filenames_view.end());
            std::ranges::sort(expected_filenames);
            std::ranges::sort(actual_filenames);
            EXPECT_RANGE_EQ(expected_filenames, actual_filenames);
        }
    }
};
