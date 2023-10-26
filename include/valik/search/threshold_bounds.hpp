#include <raptor/threshold/threshold.hpp>

namespace valik::app
{

class threshold_bounds
{
    size_t lower_bound;
    size_t upper_bound;

    public:
        threshold_bounds(search_arguments const & args, raptor::threshold::threshold const & thresh) 
        {
            std::tie(lower_bound, upper_bound) = get_bounds(args, thresh);
        };
    
    private:
        /**
         * @brief Function that returns the k-mer lemma threshold.
        */
        size_t get_kmer_lemma(search_arguments const & arguments)
        {
            uint8_t const kmer_size{arguments.shape.size()};
            size_t const kmer_lemma_minuend = arguments.pattern_size + 1u;
            size_t const kmer_lemma_subtrahend = (arguments.errors + 1u) * kmer_size;
            size_t kmer_lemma = kmer_lemma_minuend > kmer_lemma_subtrahend ? kmer_lemma_minuend - kmer_lemma_subtrahend : 0;
            return kmer_lemma;
        }

        //!TODO: missing thresholder case where percentage is set manually
        /**
         * @brief Function that returns the lower and upper bounds for the number of minimisers that have to be shared by a query pattern and a reference bin. 
        */
        std::pair<size_t, size_t> get_bounds(search_arguments const & arguments, raptor::threshold::threshold const & threshold)
        {
            uint8_t const kmer_size{arguments.shape.size()};
            size_t const kmers_per_window = arguments.window_size - kmer_size + 1;
            if (kmers_per_window == 1)
                return std::make_pair(get_kmer_lemma(arguments), 
                                      get_kmer_lemma(arguments));
            else 
            {
                size_t const kmers_per_pattern = arguments.pattern_size - kmer_size + 1;
                size_t const minimal_number_of_minimisers = kmers_per_pattern / kmers_per_window;
                size_t const maximal_number_of_minimisers = arguments.pattern_size - arguments.window_size + 1;
                return std::make_pair(threshold.get(minimal_number_of_minimisers), 
                                      threshold.get(maximal_number_of_minimisers));
            }
        }

    public:
        void print()
        {
            seqan3::debug_stream << "Shared minimiser threshold in range: [" << lower_bound << ", " << upper_bound << "]\n";
        }

};

} // namespace valik
