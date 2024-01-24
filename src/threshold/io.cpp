#include <utilities/threshold/io.hpp>

namespace valik
{

/**
 * @brief Precalculate and write out FN configuration count tables.
*/
void write_precalc_fn_confs(std::filesystem::path const & outfile)
{
    auto space = param_space();
    for (auto k = std::get<0>(space.kmer_range); k <= std::get<1>(space.kmer_range); k++)
    {
        kmer_attributes attr(k);
        std::ofstream outstr;
        outstr.open(outfile, std::ios_base::app);
        attr.serialize(outstr);
    }
}

/**
 * @brief Deserialize kmer_attributes for a single k-mer size.
*/
kmer_attributes deserialize_kmer_attributes(std::string const & kmer_attr_str)
{
    std::istringstream matrix_str(kmer_attr_str);
    std::string line;
    std::getline(matrix_str, line);
    size_t k = stoi(line.substr(line.find("k=") + 2));
        
    std::vector<std::vector<std::vector<uint64_t>>> matrix;
    std::vector<std::vector<uint64_t>> table;
    for (; std::getline(matrix_str, line); )
    {
        std::istringstream row_str(line);
        if (line.find("t=") == std::string::npos)
        {
            std::string cell;
            std::vector<uint64_t> row;
            for (; std::getline(row_str, cell, '\t'); )
            {
                row.push_back(stoi(cell));
            }
            table.push_back(row);
        }
        else if (stoi(line.substr(line.find("t=") + 2)) == 1)
        {
            continue;
        }
        else
        {
            matrix.push_back(table);
            table.clear();
        }
    }
    
    matrix.push_back(table);
    return kmer_attributes(k, matrix);
}

/**
 * @brief Read precalculated FN error configuration count tables across all k-mer sizes. 
*/
std::vector<kmer_attributes> read_fn_confs(std::filesystem::path const & infile)
{
    std::ifstream instr(infile);

    std::string line;
    std::string kmer_attr_str;
    std::vector<kmer_attributes> attr_vec;
    bool past_first(false);
    while (std::getline(instr, line)) 
    {
        if (line.find("k=") != std::string::npos)
        {
            if (past_first)
            {
                attr_vec.push_back(deserialize_kmer_attributes(kmer_attr_str));
                kmer_attr_str.clear();
            }
            past_first = true;
        }
        kmer_attr_str += line + '\n';
    }

    return attr_vec;
}

}   // namespace valik
