#pragma once

#include <utilities/threshold/filtering_request.hpp>
#include <utilities/threshold/kmer_attributes.hpp>
#include <valik/split/metadata.hpp>

namespace valik
{

/**
 * @brief Score of the objective function for a parameter set. Smaller values are better.
*/
double param_score(filtering_request const & request, param_set const & params, kmer_attributes const & attr);

/**
 * @brief Look through the parameter space to find the best kmer size and threshold. 
*/
param_set get_best_params(param_space const & space, 
                          filtering_request const & request,
                          std::vector<kmer_attributes> const & attribute_vec);

/**
 * @brief For a chosen kmer size and error rate find the best threshold. 
*/
size_t find_threshold(param_space const & space, 
                      metadata const & meta,
                      search_arguments const & arguments,
                      kmer_attributes const att);

/**
 * @brief For a chosen kmer size and some maximum error rate find the best threshold. 
*/
void find_thresholds_for_kmer_size(param_space const & space, 
                                   metadata const & meta,
                                   kmer_attributes const att, 
                                   double const max_err);

}   // namespace valik
