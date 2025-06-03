#pragma once

#include <utilities/threshold/kmer_loss.hpp>
#include <utilities/threshold/search_kmer_profile.hpp>
#include <utilities/threshold/fn_confs.hpp>

#include <valik/split/metadata.hpp>

namespace valik
{

/**
* @brief Score of the objective function for a parameter set. Smaller values are better.
*/
inline double score(kmer_loss const & attr, 
                    search_pattern const & pattern, 
                    param_set const & params, 
                    metadata const & ref_meta,
                    size_t const patterns_per_segment = PATTERNS_PER_SEGMENT)
{
    double fpr = segment_fpr(ref_meta.pattern_spurious_match_prob(params), patterns_per_segment);
    return attr.fnr_for_param_set(pattern, params) + fpr;
}

/**
 * @brief Look through the parameter space to find the best kmer size and threshold. 
*/
param_set get_best_params(search_pattern const & pattern, 
                          metadata const & ref_meta,
                          fn_confs const & fn_attr, 
                          bool const verbose);

/**
 * @brief For a chosen kmer size and some maximum error rate find the best threshold. 
*/
search_kmer_profile find_thresholds_for_kmer_size(metadata const & ref_meta,
                                                  fn_confs const & fn_attr,
                                                  utilities::kmer const & kmer, 
                                                  uint8_t const max_errors, 
                                                  bool const fast);


}   // namespace valik
