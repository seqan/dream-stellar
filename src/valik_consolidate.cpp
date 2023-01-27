#include <utilities/consolidate/consolidate.hpp>

namespace valik::app
{

//!TODO: this can live in a header
void write_output_gff(std::filesystem::path const & out_path, std::vector<stellar_match> const & matches, bool append = false)
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

void valik_consolidate(consolidation_arguments const & arguments)
{
    reference_metadata reference(arguments.ref_meta_path, false);

    std::ifstream fin(arguments.matches_in);

    std::string line;
    std::vector<stellar_match> matches;

    while (getline(fin, line))
    {
        auto line_vec = get_line_vector<std::string>(line, '\t');
        assert(line_vec.size() == 9); // Stellar GFF format output has 9 columns
        stellar_match match(line_vec, reference);
        matches.push_back(match);
    }
    fin.close();

    std::sort( matches.begin(), matches.end(), std::greater<stellar_match>());
    matches.erase( std::unique( matches.begin(), matches.end() ), matches.end() );

    write_output_gff(arguments.matches_out, matches);
}

} // namespace valik::app
