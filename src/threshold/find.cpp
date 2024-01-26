#include <utilities/threshold/find.hpp>

namespace valik
{

/**
 * @brief Score of the objective function for a parameter set. Smaller values are better.
*/
double param_score(filtering_request const & request, param_set const & params, kmer_attributes const & attr)
{
    return attr.fnr_for_param_set(request, params) + request.fpr(params.k) / (double) params.t;
}

void get_best_params(param_space const & space, 
                     filtering_request const & request,
                     std::vector<kmer_attributes> const & attribute_vec) 
{
    param_set best_params(attribute_vec[0].k, 1, space);
    auto best_score = param_score(request, best_params, attribute_vec[0]);

    std::vector<std::vector<double>> scores;
    std::vector<std::vector<double>> fn_rates;
    std::vector<double> fp_rates;
    scores.reserve(std::get<1>(space.kmer_range) - std::get<0>(space.kmer_range) + 1);
    fn_rates.reserve(std::get<1>(space.kmer_range) - std::get<0>(space.kmer_range) + 1);
    fp_rates.reserve(std::get<1>(space.kmer_range) - std::get<0>(space.kmer_range) + 1);

    for (size_t i{0}; i < attribute_vec.size(); i++)
    {
        auto att = attribute_vec[i];
        std::vector<double> kmer_scores;
        std::vector<double> kmer_fn;
        size_t k = att.k;
        for (size_t t = 1; t <= space.max_thresh; t++)
        {
            param_set params(k, t, param_space());
            auto score = param_score(request, params, att);
            kmer_scores.push_back(score);
            kmer_fn.push_back(att.fnr_for_param_set(request, params));
            if (score < best_score)
            {
                best_score = score;
                best_params = params;
            }
        }
        scores.push_back(kmer_scores);
        fn_rates.push_back(kmer_fn);
        fp_rates.push_back(request.fpr(att.k));
    }

    /*
    std::cout << '\t';
    for (size_t t{1}; t <= scores[0].size(); t++)
        std::cout << "t=" << t << '\t';
    std::cout << "FPR" << '\n';
    for (size_t i{0}; i < scores.size(); i++)
    {
        std::cout << "k=" << std::get<0>(space.kmer_range) + i << '\t';
        for (size_t j{0}; j < scores[0].size(); j++)
        {
            std::cout << fn_rates[i][j] << '\t';
        }
        std::cout << '\t' << fp_rates[i] << '\n';
    }
    */
     
    std::cout << best_params.k << '\t' <<  best_params.t << '\t' 
              << fn_rates[best_params.k - std::get<0>(space.kmer_range)][best_params.t - 1] << '\n';
}

}   // namespace valik
