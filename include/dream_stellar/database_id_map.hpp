
#pragma once

#include <dream_stellar/stellar_database_segment.hpp>

namespace dream_stellar
{

template <typename TAlphabet, typename TId = seqan2::CharString>
struct DatabaseIDMap
{
    size_t recordID(StellarDatabaseSegment<TAlphabet> const & databaseSegment) const
    {
        return recordID(databaseSegment.underlyingDatabase());
    }

    size_t recordID(seqan2::String<TAlphabet> const & database) const
    {
        seqan2::String<TAlphabet> const * begin = &databases[0];
        seqan2::String<TAlphabet> const * current = std::addressof(database);
        return current - begin;
    }

    TId const & databaseID(size_t const recordID) const
    {
        return databaseIDs[recordID];
    }

    TId const & databaseID(seqan2::String<TAlphabet> const & database) const
    {
        return databaseIDs[recordID(database)];
    }

    seqan2::StringSet<seqan2::String<TAlphabet> > const & databases;
    seqan2::StringSet<TId> const & databaseIDs;
};

} // namespace dream_stellar
