#pragma once

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

///////////////////////////////////////////////////////////////////////////////
// Imports the sequence of interest from a file,
// stores it in the StringSet seqs and their identifiers in the StringSet ids
template <typename TSequence, typename TId, typename TLen>
inline bool
_importSequencesOfInterest(char const * fileName,
                          std::vector<size_t> const & binSequences,
                          StringSet<TSequence> & seqs,
                          StringSet<TId> & ids,
                          TLen & seqLen)
{
    SeqFileIn inSeqs;
    if (!open(inSeqs, fileName))
    {
        std::cerr << "Failed to open database file.\n";
        return false;
    }

    TSequence seq;
    TId id;
    size_t seqCount{0};
    size_t foundSeqOfInterest{0};
    for (; !atEnd(inSeqs); ++seqCount)
    {
        readRecord(id, seq, inSeqs);
        seqLen += length(seq);

        if (std::find(binSequences.begin(), binSequences.end(), seqCount) != binSequences.end())
        {
            appendValue(seqs, seq, Generous());
            appendValue(ids, id, Generous());
            foundSeqOfInterest++;
            std::cout << "Loaded sequence " << id << ".\n";
        }
    }

    if (foundSeqOfInterest == binSequences.size())
        return true;

    std::cerr << "ERROR: Found " + std::to_string(foundSeqOfInterest) + " out of " + std::to_string(binSequences.size()) + " reference sequences.\n";
    return false;
}

///////////////////////////////////////////////////////////////////////////////
// Imports the sequence of interest from a file,
// stores it in the StringSet seqs and their identifiers in the StringSet ids
template <typename TSequence, typename TId>
inline bool
_importSequencesOfInterest(const char * fileName,
                          std::vector<size_t> const & binSequences,
                          StringSet<TSequence> & seqs,
                          StringSet<TId> & ids)
{
    SeqFileIn inSeqs;
    if (!open(inSeqs, fileName))
    {
        std::cerr << "Failed to open database file.\n";
        return false;
    }

    TSequence seq;
    TId id;
    size_t seqCount{0};
    size_t foundSeqOfInterest{0};
    for (; !atEnd(inSeqs); ++seqCount)
    {
        readRecord(id, seq, inSeqs);
        if (std::find(binSequences.begin(), binSequences.end(), seqCount) != binSequences.end())
        {
            appendValue(seqs, seq, Generous());
            appendValue(ids, id, Generous());
            std::cout << "Loaded sequence " << id << ".\n";
            foundSeqOfInterest++;
            if (foundSeqOfInterest == binSequences.size())
                return true;
        }
    }

    std::cerr << "ERROR: Found " + std::to_string(foundSeqOfInterest) + " out of " + std::to_string(binSequences.size()) + " reference sequences.\n";
    return false;
}

} // namespace dream_stellar
