#pragma once

#include <utilities/threshold/shared.hpp>
#include <utilities/threshold/filtering_request.hpp>
#include <utilities/threshold/kmer_attributes.hpp>

namespace valik
{

void get_best_params(param_space const & space, 
                     filtering_request const & request,
                     std::vector<kmer_attributes> const & attribute_vec);

}   // namespace valik
