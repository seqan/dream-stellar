#pragma once

#include <filesystem>

#include <valik/split/metadata.hpp>
#include <utilities/shared.hpp>

namespace valik
{

template <typename match_t>
std::vector<match_t> read_alignment_output(std::filesystem::path const & match_path,
                                           metadata const & meta,
                                           std::ios_base::openmode const mode = std::ios_base::in)
{
    std::vector<match_t> matches;
    std::ifstream fin(match_path, mode);
    std::string line;
    while (std::getline(fin, line))
    {
        //!WORKAROUND: search.gff.preliminary starts with an empty line on Clang
        if (line.empty())
            continue;

        auto line_vec = get_line_vector<std::string>(line, '\t');

        //!WORKAROUND: for valik_search_segments test that writes output file names instead of matches
        if (line_vec.size() == 1)
            break;

        assert(line_vec.size() == 9); // Stellar GFF format output has 9 columns
        match_t match(line_vec, meta);
        matches.push_back(match);
    }

    fin.close();

    return matches;
}

template <typename match_t>
void write_alignment_output(std::filesystem::path const & out_path,
                            std::vector<match_t> const & matches,
                            bool append = false)
{
    std::ofstream fout;

    if (append)
        fout.open(out_path, std::ios_base::app);
    else
        fout.open(out_path);

    for (auto match : matches)
        fout << match.to_string();

    fout.close();
}

} // namespace valik
