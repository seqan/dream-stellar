#include <utilities/threshold/find.hpp>

namespace valik
{

/**
 * @brief Score of the objective function for a parameter set. Smaller values are better.
*/
double param_score(filtering_request const & request, param_set const & params, kmer_attributes const & attr)
{
    return attr.fnr_for_param_set(request, params) + request.pattern_spurious_match_prob(params);
}

param_set get_best_params(param_space const & space, 
                          filtering_request const & request,
                          std::vector<kmer_attributes> const & attribute_vec) 
{
    param_set best_params(attribute_vec[0].k, 1, space);
    auto best_score = param_score(request, best_params, attribute_vec[0]);

    std::vector<std::vector<double>> scores;
    std::vector<std::vector<double>> fn_rates;
    std::vector<std::vector<double>> fp_rates;
    scores.reserve(std::get<1>(space.kmer_range) - std::get<0>(space.kmer_range) + 1);
    fn_rates.reserve(std::get<1>(space.kmer_range) - std::get<0>(space.kmer_range) + 1);
    fp_rates.reserve(space.max_thresh);

    for (size_t i{0}; i < attribute_vec.size(); i++)
    {
        auto att = attribute_vec[i];
        std::vector<double> kmer_scores;
        std::vector<double> kmer_fn;
        std::vector<double> kmer_fp;
        uint8_t k = att.k;
        if (k > request.l)
            break;
        else
        {
            for (uint8_t t = 1; t <= space.max_thresh; t++)
            {
                param_set params(k, t, param_space());
                auto score = param_score(request, params, att);
                kmer_scores.push_back(score);
                kmer_fn.push_back(att.fnr_for_param_set(request, params));
                kmer_fp.push_back(request.pattern_spurious_match_prob(params));
                if (score <= best_score)
                {
                    best_score = score;
                    best_params = params;
                }
            }
            scores.push_back(kmer_scores);
            fn_rates.push_back(kmer_fn);
            fp_rates.push_back(kmer_fp);
        }
    }

    /*
    std::cout << '\t';
    for (size_t i{1}; i <= space.max_thresh; i++)
        std::cout << i << '\t';
    std::cout << '\n';

    for (size_t j{0}; j < fn_rates.size(); j++)
    {
        std::cout << std::get<0>(space.kmer_range) + j << '\t';
        for (auto & cell : fn_rates[j])
            std::cout << cell << '\t';
        std::cout << '\n';
    }

    std::cout << '\t';
    for (size_t i{1}; i <= space.max_thresh; i++)
        std::cout << i << '\t';
    std::cout << '\n';

    for (size_t j{0}; j < fp_rates.size(); j++)
    {
        std::cout << std::get<0>(space.kmer_range) + j << '\t';
        for (auto & cell : fp_rates[j])
            std::cout << cell << '\t';
        std::cout << '\n';
    }
    */

    return best_params;
}

/**
 * @brief For a chosen kmer size and up to some maximum error rate find the best thresholds. 
*/
void find_thresholds_for_kmer_size(param_space const & space, 
                                  metadata const & meta,
                                  kmer_attributes const attr, 
                                  double const max_err)
{
    std::cout.precision(3);
    std::cout << "Recommended shared " << std::to_string(attr.k) << "-mer thresholds for different error rates\n";
    std::cout << "error_rate\tthreshold_kind\tthreshold\tFNR\tFP_per_pattern\tmax_query_seg_len\n";

    auto best_params = param_set(attr.k, space.max_thresh, space);
    for (uint8_t errors{1}; errors <= std::ceil(meta.segment_overlap() * max_err); errors++)
    {
        filtering_request request(errors, meta.segment_overlap(), meta.total_len, meta.seg_count);
        std::cout << errors / (double) request.l << '\t';
        if (kmer_lemma_threshold(request.l, attr.k, errors) > 1)
        {
            best_params.t = kmer_lemma_threshold(request.l, attr.k, errors);
            std::cout << "kmer lemma\t";
        }
        else
        {
            std::cout << "heuristic\t";
            double best_score = request.l;
            for (uint8_t t{1}; t <= space.max_thresh; t++)
            {
                auto params = param_set(attr.k, t, space);
                auto score = param_score(request, params, attr);
                if (score <= best_score)
                {
                    best_params = params;
                    best_score = score;
                }
            }
        }

        std::cout << std::to_string(best_params.t) << '\t' << attr.fnr_for_param_set(request, best_params) << '\t'
                  << request.pattern_spurious_match_prob(best_params) << '\n';
                  // << request.max_segment_len(best_params) << '\n';
    }
}

/**
 * @brief For a chosen kmer size and error rate find the best heuristic threshold. 
*/
uint8_t find_heuristic_threshold(metadata const & ref_meta,
                                 metadata const & query_meta,
                                 split_arguments const & arguments,
                                 kmer_attributes const attr)
{
    param_space space;
    filtering_request request(arguments.errors, arguments.pattern_size, ref_meta.total_len, ref_meta.seg_count);
    auto best_thresh = space.max_thresh;
    double best_score = arguments.pattern_size;
    for (uint8_t t{1}; t <= space.max_thresh; t++)
    {
        auto params = param_set(arguments.kmer_size, t, space);
        auto score = param_score(request, params, attr); 
        
        if (score <= best_score)
        {
            best_thresh = params.t;
            best_score = score;
        }
    }   

    return best_thresh;
}

}   // namespace valik
