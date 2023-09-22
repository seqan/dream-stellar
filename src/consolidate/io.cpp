#include <utilities/consolidate/io.hpp>

namespace valik
{

std::vector<stellar_match> read_stellar_output(std::filesystem::path const & match_path,
                                               metadata const & meta,
                                               std::ios_base::openmode const mode /* = std::ios_base::in */)
{
    std::vector<stellar_match> matches;
    std::ifstream fin(match_path, mode);
    std::string line;
    while (std::getline(fin, line))
    {
        auto line_vec = valik::get_line_vector<std::string>(line, '\t');

        //!WORKAROUND: for valik_search_segments test that writes output file names instead of matches
        if (line_vec.size() == 1)
            break;

        assert(line_vec.size() == 9); // Stellar GFF format output has 9 columns
        stellar_match match(line_vec, meta);
        matches.push_back(match);
    }

    fin.close();

    return matches;
}

void write_stellar_output(std::filesystem::path const & out_path,
                         std::vector<stellar_match> const & matches,
                         bool append /* = false */)
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
