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
    std::unordered_map<uint32_t, std::vector<size_t>> overabundant_queries{}; 
    std::vector<std::string> disabled_queries{};

    std::map<std::string, uint32_t> query_id_map;

    // <ref_ind, <query_ind, match_count>>
    std::unordered_map<size_t, std::unordered_map<uint32_t, size_t>> per_ref_match_counter{};
    // <query_ind, match_count>>
    std::unordered_map<uint32_t, size_t> total_match_counter{};
    
    decltype(matches) consolidated_matches{};
    
    for (auto & match : matches)
    {
        if (!query_id_map.count(match.qname))
            query_id_map[match.qname] = query_id_map.size();

        if ((!overabundant_queries.count(query_id_map[match.qname])) &&
            (std::count(disabled_queries.begin(), disabled_queries.end(), match.qname) == 0))
        {
            size_t ref_ind = ref_meta.ind_from_id(match.dname);
            uint32_t query_ind = query_id_map[match.qname];
            if (++per_ref_match_counter[ref_ind][query_ind] > arguments.numMatches)
                overabundant_queries[query_ind].push_back(ref_ind);
            if (++total_match_counter[query_ind] > arguments.disableThresh)
                disabled_queries.push_back(match.qname);
        }
    }
    
    /* debug
    seqan3::debug_stream << "Query fasta ID\tindex\n";
    for (auto & pair : query_id_map)
    {
        seqan3::debug_stream << pair.first << '\t' << pair.second << '\n';
    }

    seqan3::debug_stream << "Query ind\ttotal match count\n";
    for (auto & pair : total_match_counter)
    {
        seqan3::debug_stream << pair.first << '\t' << pair.second << '\n';
    }

    seqan3::debug_stream << "Per ref match count\n";
    for (auto & pair : per_ref_match_counter)
    {
        seqan3::debug_stream << pair.first << '\n';
        for (auto & query_pair : pair.second)
        {
            seqan3::debug_stream << query_pair.first << '\t' << query_pair.second << '\n'; 
        }
    }
    */

    // for <query, ref> pairs that do not appear often return all matches
    for (auto & match : matches)
    {
        bool is_disabled = (std::find(disabled_queries.begin(), disabled_queries.end(), match.qname) != disabled_queries.end()) ? true : false;
        bool is_overabundant{false};
        if (!is_disabled && overabundant_queries.count(query_id_map[match.qname]))
        {
            std::vector<size_t> ref_ids = overabundant_queries[query_id_map[match.qname]];
            is_overabundant = (std::find(ref_ids.begin(), ref_ids.end(), ref_meta.ind_from_id(match.dname)) != ref_ids.end()) ? true : false;
        }
         
        if (!is_overabundant && !is_disabled)
            consolidated_matches.emplace_back(match);
    }

    // for <query, ref> pairs that appear often return arguments.numMatches longest matches
    for (auto & pair : overabundant_queries)
    {
        std::vector<stellar_match> overabundant_matches;
        auto is_query_match = [&](auto & m){
                                                return (query_id_map[m.qname] == pair.first) && 
                                                (std::count(pair.second.begin(), pair.second.end(), ref_meta.ind_from_id(m.dname)) > 0);
                                            };

        for (auto & m : matches | std::views::filter(is_query_match))
            overabundant_matches.push_back(m);

        std::sort(overabundant_matches.begin(), overabundant_matches.end(), stellar_match::length_order()); // sort in order of increasing length
        consolidated_matches.insert(consolidated_matches.end(), overabundant_matches.end() - arguments.numMatches, overabundant_matches.end());
    }

    // debug
    if (arguments.verbose)
    {
        for (auto & pair : overabundant_queries)
        {
            seqan3::debug_stream << "Query: " << pair.first << "\nHas too many matches in references ";    
            for (auto & ref : pair.second)
                seqan3::debug_stream << ref << '\t';

            seqan3::debug_stream << '\n';
        }
    }
    
    // write out fasta file of disabled queries
    if (disabled_queries.size() > 0)
    {
        using input_file_t = seqan3::sequence_file_input<dna4_traits, seqan3::fields<seqan3::field::seq, seqan3::field::id>>;
        input_file_t fin{arguments.query_file};
        using query_record_type = typename decltype(fin)::record_type;
        
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
