
#pragma once

#include <dream_stellar/utils/fraction.hpp>

namespace dream_stellar
{

struct EPSMatchOptions
{
    dream_stellar::utils::fraction epsilon{5, 100}; // maximal error rate
    double numEpsilon{0.05};
    unsigned minLength{100}; // minimal length of an epsilon-match
};

} // namespace dream_stellar
