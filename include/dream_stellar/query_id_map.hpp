#pragma once

#include <dream_stellar/stellar_index.hpp>
#include <dream_stellar/stellar_query_segment.hpp>
#include <dream_stellar/stellar_types.hpp>

namespace dream_stellar
{

template <typename alphabet_t, typename sequence_reference_t = std::span< const alphabet_t>, typename TId = std::string>
struct QueryIDMap
{
    size_t recordID(sequence_reference_t const & query) const
    {
        sequence_reference_t const * begin = &queries[0];
        sequence_reference_t const * current = std::addressof(query);
        return current - begin;
    }

    std::vector<sequence_reference_t> const & queries;
};

} // namespace dream_stellar
