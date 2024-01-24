#include <utilities/threshold/find.hpp>

namespace valik
{

void get_best_params(param_space const & space, 
                     filtering_request const & request,
                     std::vector<kmer_attributes> const & attribute_vec) 
{
    param_set best_params(attribute_vec[0].k, 1, space);
    auto best_score = attribute_vec[0].score(request, best_params);

    std::vector<std::vector<double>> scores;
    std::vector<std::vector<double>> fn_rates;
    std::vector<double> fp_rates;
    scores.reserve(std::get<1>(space.kmer_range) - std::get<0>(space.kmer_range) + 1);
    fn_rates.reserve(std::get<1>(space.kmer_range) - std::get<0>(space.kmer_range) + 1);
    fp_rates.reserve(std::get<1>(space.kmer_range) - std::get<0>(space.kmer_range) + 1);

    for (size_t i{i}; i < attribute_vec.size(); i++)
    {
        auto att = attribute_vec[i];
        std::vector<double> kmer_scores;
        std::vector<double> kmer_fn;
        size_t k = att.k;
        for (size_t t = 1; t <= space.max_thresh; t++)
        {
            param_set params(k, t, param_space());
            auto score = att.score(request, params);
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
    std::cout << "Chose k=" << best_params.k << " and t=" <<  best_params.t << '\n';
    */
}

}   // namespace valik
