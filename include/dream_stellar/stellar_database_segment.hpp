#pragma once

#include <seqan/seq_io.h>

#include <dream_stellar/stellar_sequence_segment.hpp>
#include <dream_stellar/stellar_types.hpp>

namespace dream_stellar
{

using namespace seqan2;

template <typename TAlphabet>
struct StellarDatabaseSegment : public StellarSequenceSegment<TAlphabet>
{
    using TBase = StellarSequenceSegment<TAlphabet>;

    using typename TBase::TInfixSegment;
    using TNestedFinderSegment = seqan2::Segment<TInfixSegment, seqan2::InfixSegment>;

    using TBase::TBase; // import constructor

    static StellarDatabaseSegment<TAlphabet> fromFinderMatch(TInfixSegment const & finderMatch)
    {
        seqan2::String<TAlphabet> const & underlyingDatabase = host(finderMatch);
        return {underlyingDatabase, seqan2::beginPosition(finderMatch), seqan2::endPosition(finderMatch)};
    }

    seqan2::String<TAlphabet> const & underlyingDatabase() const &
    {
        return this->underlyingSequence();
    }

    TNestedFinderSegment asFinderSegment() const
    {
        seqan2::String<TAlphabet> const & _database = underlyingDatabase();
        auto finderInfix = this->asInfixSegment();

        TInfixSegment const finderInfixSeq = infix(_database, 0, length(_database));
        TNestedFinderSegment finderSegment(finderInfixSeq,
            seqan2::beginPosition(finderInfix) - seqan2::beginPosition(_database),
            seqan2::endPosition(finderInfix) - seqan2::beginPosition(_database));
        return finderSegment;
    }
};

//!TODO: could not convert ‘span<alphabet_adaptor<[...]>,[...]>’ to ‘span<alphabet_adaptor<[...]>,[...]>
template <typename alphabet_t>
std::span<alphabet_t> get_database_segment(std::vector<std::vector<alphabet_t>> const & databases,
                                           StellarOptions const & options,
                                           bool const reverse = false)
{
    auto database = std::span(databases[options.binSequences[0]]);

    if (database.size() < options.segmentEnd)
        throw std::runtime_error{"Segment end out of range"};

    if (options.segmentEnd <= options.segmentBegin)
        throw std::runtime_error{"Incorrect segment definition"};

    if (options.segmentEnd < options.minLength + options.segmentBegin)
        throw std::runtime_error{"Segment shorter than minimum match length"};

    if (reverse)
    {
        return database.subspan(database.size() - options.segmentEnd /* offset */, 
                                options.segmentEnd - options.segmentBegin /* count */);
    }

    return database.subspan(options.segmentBegin /* offset */, options.segmentEnd - options.segmentBegin /* count */);
}

} // namespace dream_stellar
