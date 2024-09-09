#pragma once

#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <dream_stellar/options/dream_options.hpp>
#include <dream_stellar/options/eps_match_options.hpp>
#include <dream_stellar/options/index_options.hpp>
#include <dream_stellar/options/verifier_options.hpp>

namespace dream_stellar
{

///////////////////////////////////////////////////////////////////////////////
// Options for Stellar
struct StellarOptions : public EPSMatchOptions, public IndexOptions, public VerifierOptions, public DREAMOptions {
    // i/o options
    std::string databaseFile;        // name of database file
    std::string queryFile;           // name of query file
    std::string outputFile{"stellar.gff"};          // name of result file
    std::string disabledQueriesFile{"stellar.disabled.fasta"}; // name of result file containing disabled queries
    std::string outputFormat{"gff"};        // Possible formats: gff, text
    std::string alphabet{"dna5"};            // Possible values: dna, rna, protein, char
    bool write_time;        // write running time to standard output

    // more options
    bool forward{true};               // compute matches to forward strand of database
    bool onlyForward{false};
    bool reverse{true};               // compute matches to reverse complemented database
    bool onlyReverse{false};

    size_t disableThresh = std::numeric_limits<size_t>::max();     // maximal number of matches allowed per query before disabling verification of hits for that query
    size_t compactThresh = 500;     // number of matches after which removal of overlaps and duplicates is started
    size_t numMatches = 50;        // maximal number of matches per query and database
    size_t maxRepeatPeriod = 1;   // maximal period of low complexity repeats to be filtered
    size_t minRepeatLength = 1000;   // minimal length of low complexity repeats to be filtered
    bool verbose{false};               // verbose mode

    static constexpr size_t kmerCount(size_t sequenceLength, size_t kmerSize)
    {
        assert(kmerSize > 0u);
        assert(sequenceLength >= kmerSize - 1u);
        // number of kmers
        return sequenceLength + 1u - kmerSize;
    }

    static constexpr size_t kmerLemma(size_t sequenceLength, size_t kmerSize, size_t errors)
    {
        size_t maxAffectedKMers = kmerSize * errors;
        size_t count = kmerCount(sequenceLength, kmerSize);
        return std::max(count, maxAffectedKMers) - maxAffectedKMers;
    }

    static constexpr size_t pigeonholeLemma(size_t sequenceLength, size_t errors)
    {
        assert(sequenceLength >= errors);
        // how many consecutive chars must be error free
        using difference_t = utils::fraction::difference_t;
        return ceil(utils::fraction{static_cast<difference_t>(sequenceLength - errors), errors + 1});
    }

    static constexpr size_t minLengthWithExactError(size_t absoluteError, utils::fraction epsilon)
    {
        if (epsilon.numerator() == 0)
            return std::numeric_limits<size_t>::max();

        using difference_t = utils::fraction::difference_t;
        return ceil(utils::fraction{static_cast<difference_t>(absoluteError), 1} / epsilon);
    }

    static constexpr size_t absoluteErrors(utils::fraction epsilon, size_t sequenceLength)
    {
        using difference_t = utils::fraction::difference_t;
        return floor(utils::fraction{static_cast<difference_t>(sequenceLength), 1} * epsilon);
    }

};

}
