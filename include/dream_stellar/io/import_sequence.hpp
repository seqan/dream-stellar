#pragma once

#include <type_traits> 
#include <seqan/seq_io.h>

namespace dream_stellar
{

using namespace seqan2;

template <typename TId>
inline bool
_checkUniqueId(std::set<TId> & uniqueIds, TId const & id)
{
    TId shortId;

    // (cut at first whitespace)
    for (auto it = begin(id); it != end(id) && *it > ' '; ++it)
    {
        appendValue(shortId, *it);
    }

    auto [it, added] = uniqueIds.insert(shortId);

    return added;
}

template <typename input_t, typename collection_t, typename stream_t>
inline bool _import_database_sequences(input_t const & file_input,
                                       collection_t & seqs,
                                       std::vector<std::string> & ids,
                                       uint64_t & seq_len,
                                       stream_t & str_out,
                                       stream_t & str_err)
{
    bool ids_unique{true};
    size_t seq_count{0};
    
    auto record_intake_lambda = [&](auto const & record) 
    { 
        ids_unique &= (std::find(ids.begin(), ids.end(), record.id()) != ids.end());
        seq_len += record.sequence().size();
        seqs.emplace_back(record.sequence());
        ids.emplace_back(record.id());
        seq_count++; 
    }; 
    
    if constexpr (std::is_same<input_t, std::string>::value)
    {
        seqan3::sequence_file_input<valik::dna4_adaptor_traits> fin{file_input};
        for (auto & record : fin)
        {
            record_intake_lambda(record);
        }
    }
    else if constexpr (std::is_same<input_t, std::vector<std::vector<std::string>>>::value)
    {
        for (auto & bin : file_input)
        {
            for (auto & bin_file : bin)
            {
                seqan3::sequence_file_input<valik::dna4_adaptor_traits> fin{bin_file};
                for (auto & record : bin_file)
                {
                    record_intake_lambda(record);
                }
            }
        }
    }
    else
    {
        str_err << "WARNING: Unknown database file input\n";
    }

    str_out << "Loaded " << seq_count << " adapted database sequence" << ((seq_count > 1) ? "s." : ".") << std::endl;
    if (!ids_unique)
        str_err << "WARNING: Non-unique adapted database ids. Output can be ambiguous.\n";
    return true;
}

} // namespace dream_stellar
