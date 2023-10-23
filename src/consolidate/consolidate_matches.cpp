#include <utilities/consolidate/consolidate_matches.hpp>

namespace valik
{

void consolidate_matches(search_arguments const & arguments)
{
    auto ref_meta = metadata(arguments.ref_meta_path);
    auto matches = read_stellar_output(arguments.all_matches, ref_meta);

    std::sort( matches.begin(), matches.end(), std::greater<stellar_match>());
    matches.erase( std::unique( matches.begin(), matches.end() ), matches.end() );

    std::unordered_map<uint32_t, std::vector<size_t>> overabundant_queries{}; 
    std::vector<std::string> disabled_queries{};

    std::map<std::string, uint32_t> query_id_map;

    // <ref_ind, <query_ind, match_count>>
    std::unordered_map<size_t, std::unordered_map<uint32_t, size_t>> per_ref_match_counter{};
    // <query_ind, match_count>>
    std::unordered_map<uint32_t, size_t> total_match_counter{};
    
    for (auto & match : matches)
    {
        if (!query_id_map.count(match.qname))
            query_id_map[match.qname] = query_id_map.size();

        if ((overabundant_queries.count(query_id_map[match.qname]) == 0) &&
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

    decltype(matches) consolidated_matches{};
    for (auto & match : matches)
    {
        if (overabundant_queries.size() > 0)
        {
            bool is_overabundant = (overabundant_queries.count(query_id_map[match.qname]) > 0) ? true : false;
            if (!is_overabundant)
                consolidated_matches.emplace_back(std::move(match));
        }
        else 
            consolidated_matches.emplace_back(std::move(match));
    }

    if (overabundant_queries.size() > 0)
    {
        for (auto & pair : overabundant_queries)
        {
            std::vector<stellar_match> overabundant_matches;
            auto is_query_match = [&](auto & m){
                                                    return (query_id_map[m.qname] == pair.first) && 
                                                    (std::count(pair.second.begin(), pair.second.end(), ref_meta.ind_from_id(m.dname)) > 0);
                                                };
            for (auto & m : matches | std::views::filter(is_query_match)) 
                overabundant_matches.push_back(m);

            std::sort(overabundant_matches.begin(), overabundant_matches.end(), stellar_match::length_order());
            consolidated_matches.insert(consolidated_matches.end(), overabundant_matches.begin(), overabundant_matches.begin() + arguments.numMatches);
        }
    }

    if (disabled_queries.size() > 0)
    {
        using input_file_t = seqan3::sequence_file_input<dna4_traits, seqan3::fields<seqan3::field::seq, seqan3::field::id>>;
        input_file_t fin{arguments.query_file};
        using query_record_type = typename decltype(fin)::record_type;
        
        seqan3::sequence_file_output fdisabled(arguments.disabledQueriesFile);
        
        for (auto & record : fin)
            if (std::find(disabled_queries.begin(), disabled_queries.end(), record.id()) != disabled_queries.end())
                fdisabled.push_back(record);
    }

    write_stellar_output(arguments.out_file, consolidated_matches);
}

}  // namespace valik
