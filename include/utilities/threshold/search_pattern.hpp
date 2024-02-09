#pragma once

#include <utilities/threshold/basics.hpp>

namespace valik
{

/**
 * @brief Define an approximate local alignment of a minimum length and maximum number of errors. 
 *        Same as Stellar epsilon matches.  
*/
struct search_pattern
{
    uint8_t e;
    size_t l;

    /**
     * @brief Total number of error configurations.
    */
    uint64_t total_conf_count() const
    {
        return combinations(e, l);
    }
};

}   // namespace valik
