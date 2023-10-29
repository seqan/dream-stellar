#include <utilities/consolidate/consolidate_matches.hpp>

namespace valik
{

/**
 * @brief Function that truncates the fasta id if it contains whitespace.
*/
std::string truncate_fasta_id(std::string const & id)
{
    auto first_whitespace = id.find_first_of(" ");
    if (first_whitespace == std::string::npos)
        return id;

    return id.substr(0, first_whitespace);
}

void consolidate_matches(search_arguments const & arguments)
{
    auto ref_meta = metadata(arguments.ref_meta_path);
    auto matches = read_stellar_output(arguments.all_matches, ref_meta);

    std::sort(matches.begin(), matches.end(), std::greater<stellar_match>());
    matches.erase( std::unique( matches.begin(), matches.end() ), matches.end() );

    // <query_ind, <refs>>
    std::set<std::string> overabundant_queries{}; 
    std::set<std::string> disabled_queries{};

    // <query_ind, match_count>>
    std::map<std::string, size_t> total_match_counter{};
    
    decltype(matches) consolidated_matches{};
    
    for (auto & match : matches)
    {
        if ((std::count(overabundant_queries.begin(), overabundant_queries.end(), match.qname) == 0) &&
            (std::count(disabled_queries.begin(), disabled_queries.end(), match.qname) == 0))
        {
            if (++total_match_counter[match.qname] >= arguments.disableThresh)
                disabled_queries.emplace(match.qname);
            else
            {
                if (++total_match_counter[match.qname] > arguments.numMatches)
                    overabundant_queries.emplace(match.qname);
            }            
        }
    }
    
    // for <query, ref> pairs that do not appear often return all matches
    for (auto & match : matches)
    {
        bool is_disabled = (std::find(disabled_queries.begin(), disabled_queries.end(), match.qname) != disabled_queries.end());
        bool is_overabundant = (!is_disabled && (overabundant_queries.find(match.qname) != overabundant_queries.end()));
         
        if (!is_overabundant && !is_disabled)
            consolidated_matches.emplace_back(match);
    }

    // for <query, ref> pairs that appear often return arguments.numMatches longest matches
    for (auto & query_id : overabundant_queries)
    {
        std::vector<stellar_match> overabundant_matches;
        auto is_query_match = [&](auto & m){
                                                return (m.qname == query_id);
                                            };

        for (auto & m : matches | std::views::filter(is_query_match))
            overabundant_matches.push_back(m);

        std::sort(overabundant_matches.begin(), overabundant_matches.end(), stellar_match::length_order()); // sort in order of increasing length
        consolidated_matches.insert(consolidated_matches.end(), overabundant_matches.end() - arguments.numMatches, overabundant_matches.end());
    }

    // debug
    if (arguments.verbose)
    {
        seqan3::debug_stream << "Overabundant queries\n";
        for (auto & query_id : overabundant_queries)
        {
            seqan3::debug_stream << query_id << '\n'; 
        }
    }
    
    // write out fasta file of disabled queries
    if (disabled_queries.size() > 0)
    {
        using input_file_t = seqan3::sequence_file_input<dna4_traits, seqan3::fields<seqan3::field::seq, seqan3::field::id>>;
        input_file_t fin{arguments.query_file};
        
        seqan3::sequence_file_output fdisabled(arguments.disabledQueriesFile);
        
        for (auto & record : fin)
        {
            if (std::find(disabled_queries.begin(), disabled_queries.end(), truncate_fasta_id(record.id())) != disabled_queries.end())
                fdisabled.push_back(record);
        }

        // debug
        if (arguments.verbose)
            seqan3::debug_stream << "Disabled " << disabled_queries.size() << " queries.\n";
    }

    write_stellar_output(arguments.out_file, consolidated_matches);
}

}  // namespace valik
