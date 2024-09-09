#pragma once

#include <seqan/seq_io.h>

#include <dream_stellar/stellar_sequence_segment.hpp>
#include <dream_stellar/stellar_types.hpp>

namespace dream_stellar
{

using namespace seqan2;

//!TODO: remove obsolete functions
template <typename alphabet_t>
struct StellarDatabaseSegment : public StellarSequenceSegment<alphabet_t>
{
    using TBase = StellarSequenceSegment<alphabet_t>;

    using typename TBase::TInfixSegment;
    
    //!TODO: why is it nested?
    using TNestedFinderSegment = seqan2::Segment<TInfixSegment, seqan2::InfixSegment>;

    using TBase::TBase; // import constructor

    static StellarDatabaseSegment<alphabet_t> fromFinderMatch(TInfixSegment const & finderMatch)
    {
        std::span<alphabet_t> const & underlyingDatabase = host(finderMatch);
        return {underlyingDatabase, seqan2::beginPosition(finderMatch), seqan2::endPosition(finderMatch)};
    }

    std::span<const alphabet_t> const & underlyingDatabase() const
    {
        return this->underlyingSequence();
    }

    TNestedFinderSegment asFinderSegment() const
    {
        std::span<const alphabet_t> const & _database = underlyingDatabase();
        auto finderInfix = this->asInfixSegment();

        TInfixSegment const finderInfixSeq = infix(_database, 0, length(_database));
        TNestedFinderSegment finderSegment(finderInfixSeq,
            seqan2::beginPosition(finderInfix) - seqan2::beginPosition(_database),
            seqan2::endPosition(finderInfix) - seqan2::beginPosition(_database));
        return finderSegment;
    }
};

} // namespace dream_stellar
