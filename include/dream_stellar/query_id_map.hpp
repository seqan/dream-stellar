#pragma once

#include <dream_stellar/stellar_query_segment.hpp>

#include <valik/search/query_record.hpp>

namespace dream_stellar
{

/**
 * @brief Associate a query ID with the corresponding segment sequence.
 */
template <typename alphabet_t>
struct query_id_map
{
    using rec_t = valik::shared_query_record<alphabet_t>;
    std::vector<rec_t> & records;
    
    dream_stellar::StellarQuerySegment<const alphabet_t> segment_from_id(unsigned const & query_id) const
    {
        if (query_id >= records.size())
            throw std::runtime_error("Query index " + std::to_string(query_id) + " is out of range [0, " 
                                                    + std::to_string(records.size() - 1) + "]");
        rec_t & shared_rec = records[query_id];
        return shared_rec.asStellarSegment();
    }
};

} // namespace dream_stellar
