
#pragma once

#include <dream_stellar/stellar_index.hpp>
#include <dream_stellar/stellar_query_segment.hpp>
#include <dream_stellar/stellar_types.hpp>

namespace dream_stellar
{

template <typename TAlphabet, typename TId = CharString>
struct QueryIDMap
{
    size_t recordID(String<TAlphabet> const & query) const
    {
        String<TAlphabet> const * begin = &queries[0];
        String<TAlphabet> const * current = std::addressof(query);
        return current - begin;
    }

    StringSet<String<TAlphabet> > const & queries;
};

} // namespace dream_stellar
