#pragma once

#include <utilities/threshold/kmer_loss.hpp>

namespace valik
{

/**
 * @brief Gather estimates for the number of false negatives across a range of k-mer lengths, error rates, thresholds and match lengths. 
 *   
 * @param space Parameter space.
*/
struct fn_confs
{
    const param_space space;
    
    private:
        std::vector<kmer_loss> attr_vec;

        /**
         * @brief Serialization file path.
         */
        std::filesystem::path fn_filename()
        {
            std::string outfile = "fn_err_conf_e" + std::to_string(space.max_errors) + "_t" + std::to_string(space.max_thresh) + 
                                                    "_l" + std::to_string(space.max_len) + "_k" + 
                                                    std::to_string(space.min_k()) + "_" + 
                                                    std::to_string(space.max_k()) + ".tsv";
            return outfile;
        }

        /**
         * @brief Precalculate and write out FN configuration count tables.
        */
        void precalc_fn_confs()
        {
            auto outfile = fn_filename();
            for (auto k = space.min_k(); k <= space.max_k(); k++)
            {
                kmer_loss attr(k, space);
                attr_vec.push_back(attr);
                std::ofstream outstr;
                outstr.open(outfile, std::ios_base::app);
                attr.serialize(outstr);
            }
        }

        /** //TODO: use cereal
         * @brief Read precalculated FN error configuration count tables across all k-mer sizes. 
        */
        bool read_fn_confs()
        {
            auto infile = fn_filename();
            if (!std::filesystem::exists(infile))
                return false;

            std::ifstream instr(infile);
            std::string line;
            std::string kmer_attr_str;
            bool past_first(false);
            while (std::getline(instr, line)) 
            {
                if (line.find("k=") != std::string::npos)
                {
                    if (past_first)
                    {
                        attr_vec.push_back(kmer_loss(kmer_attr_str));
                        kmer_attr_str.clear();
                    }
                    past_first = true;
                }
                kmer_attr_str += line + '\n';
            }

            attr_vec.push_back(kmer_loss(kmer_attr_str));
            return true;
        }

    public:
        fn_confs(param_space const & s) : space(s)
        {
            if (!read_fn_confs())
                precalc_fn_confs();
        }

        kmer_loss & get_kmer_loss(uint8_t const k) const
        {
            if (k < space.min_k() || k > space.max_k())
            {
                throw std::runtime_error("k-mer length " + std::to_string(k) + " is out of range [" + 
                      std::to_string(space.min_k()) + ", " + std::to_string(space.max_k()) + "]");
            }
            
            return attr_vec[k - space.min_k()];
        }
};

} // namespace valik
