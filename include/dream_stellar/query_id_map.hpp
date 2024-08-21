#pragma once

#include <dream_stellar/stellar_query_segment.hpp>

#include <valik/search/query_record.hpp>

namespace dream_stellar
{

template <typename alphabet_t, typename sequence_container_t = std::vector<alphabet_t>, 
          typename sequence_reference_t = std::span<const alphabet_t>>
class QueryIDMap
{
    std::vector<valik::shared_query_record<sequence_reference_t>> queries;

    public:

        QueryIDMap(std::vector<valik::shared_query_record<sequence_container_t>> const & records)
        {
            for (auto & record : records)
                queries.emplace_back(record.id, record.get_start(), record.get_len(), record.underlyingData);
        }

        dream_stellar::StellarQuerySegment<sequence_reference_t> segment_from_id(unsigned const & query_id) const
        {
            if (query_id >= queries.size())
                throw std::runtime_error("Query index " + std::to_string(query_id) + " is out of range [0, " 
                                                        + std::to_string(queries.size() - 1) + "]");
            valik::shared_query_record<sequence_reference_t> & shared_rec = queries[query_id];

            return shared_rec.get_seqan_segment();
        }

};

} // namespace dream_stellar
