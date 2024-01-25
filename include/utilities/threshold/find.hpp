#pragma once

#include <utilities/threshold/shared.hpp>
#include <utilities/threshold/filtering_request.hpp>
#include <utilities/threshold/kmer_attributes.hpp>

namespace valik
{

/**
 * @brief Score of the objective function for a parameter set. Smaller values are better.
*/
double param_score(filtering_request const & request, param_set const & params, kmer_attributes const & attr);

void get_best_params(param_space const & space, 
                     filtering_request const & request,
                     std::vector<kmer_attributes> const & attribute_vec);

}   // namespace valik
