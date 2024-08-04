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

///////////////////////////////////////////////////////////////////////////////
// Imports sequences from a file,
// stores them in the StringSet seqs and their identifiers in the StringSet ids
template <typename TSequence, typename TId, typename TLen, typename TStream>
inline bool
_importAllSequences(char const * fileName,
                    CharString const & name,
                    StringSet<TSequence> & seqs,
                    StringSet<TId> & ids,
                    TLen & seqLen,
                    TStream & strOut,
                    TStream & strErr)
{
    SeqFileIn inSeqs;
    if (!open(inSeqs, fileName))
    {
        strErr << "Failed to open " << name << " file." << std::endl;
        return false;
    }

    std::set<TId> uniqueIds; // set of short IDs (cut at first whitespace)
    bool idsUnique = true;

    TSequence seq;
    TId id;
    size_t seqCount{0};
    for (; !atEnd(inSeqs); ++seqCount)
    {
        readRecord(id, seq, inSeqs);

        if (name == "database")
            seqLen += length(seq);

        idsUnique &= _checkUniqueId(uniqueIds, id);

        appendValue(seqs, seq, Generous());
        appendValue(ids, id, Generous());
    }

    strOut << "Loaded " << seqCount << " " << name << " sequence" << ((seqCount > 1) ? "s." : ".") << std::endl;
    if (!idsUnique)
        strErr << "WARNING: Non-unique " << name << " ids. Output can be ambiguous.\n";
    return true;
}

} // namespace dream_stellar
