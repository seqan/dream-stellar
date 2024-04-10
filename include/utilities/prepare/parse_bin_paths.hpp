#pragma once

#include <valik/shared.hpp>
#include <valik/split/metadata.hpp>

namespace valik
{

inline auto parse_bin_paths(build_arguments const & arguments)
{
    std::vector<std::vector<std::string>> minimiser_files{};
    if (arguments.bin_path.size() > 1)
    {
        for (std::vector<std::string> bin_files : arguments.bin_path)
        {
            std::vector<std::string> bin_headers;
            for (std::filesystem::path file : bin_files)
            {
                bin_headers.push_back(file.replace_extension("minimiser"));
                //seqan3::debug_stream << bin_headers[bin_headers.size() - 1] << '\n';
            }
            minimiser_files.push_back(bin_headers);
        }
    }
    else
    {
        valik::metadata meta(arguments.ref_meta_path); 
        for (size_t bin{0}; bin < arguments.bins; bin++)
        {
            std::filesystem::path file = arguments.bin_path[0][0];
            minimiser_files.emplace_back((std::vector<std::string>){file.replace_extension(std::to_string(bin) + ".minimiser")});
            //seqan3::debug_stream << minimiser_files[minimiser_files.size() - 1][0] << '\n';
        }
    }

    return minimiser_files;
}

} // namespace valik
