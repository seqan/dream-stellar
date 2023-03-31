#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

#include <valik/split/reference_metadata.hpp>
#include <hibf/print_matrix.hpp>

namespace hibf
{

/*!\brief Returns the smallest natural number that is greater or equal to `value` and a multiplicative of 64.
* \param[in] value The Input value that is smaller or equal to the return value.
*/
[[nodiscard]] constexpr size_t next_multiple_of_64(size_t const value) noexcept
{
    return ((value + 63) >> 6) << 6;
}

/*!\brief Distributes x Technical Bins across y User Bins while minimizing the maximal Technical Bin size
 *
 * # Terminology
 *
 * ## Technical Bin
 * \copydetails simple_binning::num_technical_bins
 *
 * ## User Bin
 * \copydetails simple_binning::num_user_bins
 *
 * ## Notation
 *  | Name    | Description                                                                 |
 *  |---------|---------------------------------------------------------------------------- |
 *  | **x**   | Number of Technical Bins (TB)                                               |
 *  | **y**   | Number of User Bins (UB)                                                    |
 *  | **b_i** | The bin size (kmer content) of Technical Bin \f$i\f$                            |
 *  | **c_j** | The kmer content of User Bin \f$j\f$                                            |
 *  | **M**   | A DP matrix that tracks the maximum technical bin size \f$\max_{i} (b_i)\f$.|
 *
 *  \attention The number of technical bins **x** must be greater that the number of user bins **y** for this algorithm.
     *            If you want to use less technical bins than user bins, see the hierarchical_binning algorithm.
 *
 * # Algorithm
 *
 * Since the size of the IBF depends on the maximal Technical Bin size, we want to minimize \f$ max_{i} (b_i)\f$.
 *
 * Let \f$r = x - y\f$ be the surplus of TBs
 *
 * ## Initialization
 * <img src="execute_init.png" align="left"  width="10%"/>
 *
 * <br><br>
 * \f$\qquad \forall_{i \in [0,r]} \quad M_{i,0} = \frac{c_0}{i + 1}\f$
 * <br><br><br><br><br><br><br><br><br><br>
 *
 * ## Recursion
 * <img src="execute_recursion.png" align="left"  width="10%"/>
 *
 * <br><br>
 * \f$\forall_{i,j} \quad M_{i,j} = \min_{i' \in [i - r - 1, i - 1]} \max(M_{i',j-1}, \frac{c_j}{i - i'})\f$
 * <br><br><br><br><br><br><br><br><br><br>
 *
 * ## Backtracking
 *
 * Assume we filled a trace matrix **T** during the computation of **M**.
 *
 * We now want to recover the number of bins **n_j** for each User Bin **j**.
 *
 * <img src="execute_backtracking.png" align="left"  width="10%"/>
 *
 * Backtracking pseudo code:
 * ```
 * // Start at the bottom-right cell.
 * j = y - 1;
 * i = x - 1;
 * n = array(y); // array of length y
 *
 * while (j > 0)
 * {
 *     next_i = T[i][j];
 *     n[j] = i - next_i;
 *     i = next_i;
 *     j = j - 1;
 * }
 * ```
 */
class simple_binning
{
private:
    //!\brief The data input: filenames associated with the user bin and a kmer count per user bin.
    valik::reference_metadata const * data{nullptr};

    /*!\brief The number of User bins.
     *
     * The user may impose a structure on his sequence data in the form of *logical groups* (e.g. species).
     * When querying the IBF, the user is interested in an answer that differentiates between these groups.
     */
    size_t const num_user_bins{};

    /*!\brief The number of Technical bins.
     *
     * A *Technical Bin* represents an actual bin in the binning directory.
     * In the IBF, it stores its kmers in a **single Bloom Filter** (which is interleaved with all the other BFs).
     */
    size_t const num_technical_bins{};

public:
    simple_binning() = default;                                   //!< Defaulted.
    simple_binning(simple_binning const &) = default;             //!< Defaulted.
    simple_binning & operator=(simple_binning const &) = default; //!< Defaulted.
    simple_binning(simple_binning &&) = default;                  //!< Defaulted.
    simple_binning & operator=(simple_binning &&) = default;      //!< Defaulted.
    ~simple_binning() = default;                                  //!< Defaulted.

    /*!\brief The constructor from user bin names, their kmer counts and a configuration.
     * \param[in] data_ The filenames and kmer counts associated with the user bin, as well as the ostream buffer.
     * \param[in] num_bins (optional) The number of technical bins.
     *
     * If the `num_bins` parameter is omitted or set to 0, then number of technical bins used in this algorithm
     * is automatically set to the next multiple of 64 given the number of user bins (e.g. \#UB = 88 -> \#TB = 124).
     *
     * \attention The number of technical bins must be greater or equal to the number of user bins!
     *            If you want to use less technical bins than user bins, see the hierarchical_binning algorithm.
     */
    simple_binning(valik::reference_metadata & data_, size_t const num_bins = 0) :
        data{std::addressof(data_)},
        num_user_bins{data->sequences.size()},
        num_technical_bins{num_bins ? num_bins : next_multiple_of_64(num_user_bins)}
    {
        assert(data != nullptr);

        if (num_user_bins > num_technical_bins)
        {
            throw std::runtime_error{"You cannot have less technical bins than user bins for this simple binning "
                                     "algorithm. Please see the hierarchical_binning algorithm or increase the number "
                                     "of technical bins."};
        }
    }

    size_t get_num_technical_bins() const
    {
        return num_technical_bins;
    }

    //!\brief Executes the simple binning algorithm and layouts user bins into technical bins.
    size_t execute()
    {
        assert(data != nullptr);

        std::vector<std::vector<size_t>> matrix(num_technical_bins); // rows
        for (auto & v : matrix)
            v.resize(num_user_bins, std::numeric_limits<size_t>::max()); // columns

        std::vector<std::vector<size_t>> trace(num_technical_bins); // rows
        for (auto & v : trace)
            v.resize(num_user_bins, std::numeric_limits<size_t>::max()); // columns

        size_t const extra_bins = num_technical_bins - num_user_bins + 1;

        // initialize first column (first row is initialized with inf)
        double const ub_cardinality = static_cast<double>(data->sequences[0].len);
        for (size_t i = 0; i < extra_bins; ++i)
        {
            // no FPR correction because cardinality is based on sequence length not k-mer content
            matrix[i][0] = ub_cardinality / (i + 1);
        }

        // we must iterate column wise
        for (size_t j = 1; j < num_user_bins; ++j)
        {
            double const ub_cardinality = static_cast<double>(data->sequences[j].len);

            for (size_t i = j; i < j + extra_bins; ++i)
            {
                size_t minimum{std::numeric_limits<size_t>::max()};

                for (size_t i_prime = j - 1; i_prime < i; ++i_prime)
                {
                    size_t score = std::max<size_t>(ub_cardinality / (i - i_prime), matrix[i_prime][j - 1]);

                    // std::cout << "j:" << j << " i:" << i << " i':" << i_prime << " score:" << score << std::endl;

                    minimum = (score < minimum) ? (trace[i][j] = i_prime, score) : minimum;
                }

                matrix[i][j] = minimum;
            }
        }

        // print_matrix(matrix, num_technical_bins, num_user_bins, std::numeric_limits<size_t>::max());
        // print_matrix(trace, num_technical_bins, num_user_bins, std::numeric_limits<size_t>::max());

        // backtracking
        size_t trace_i = num_technical_bins - 1;
        size_t trace_j = num_user_bins - 1;

        size_t max_id{};
        size_t max_size{};

        size_t bin_id{};
        size_t const optimal_score{matrix[trace_i][trace_j]};

        while (trace_j > 0)
        {
            size_t next_i = trace[trace_i][trace_j];
            size_t const kmer_count = data->sequences[trace_j].len;
            size_t const number_of_bins = (trace_i - next_i);
            size_t const kmer_count_per_bin = (kmer_count + number_of_bins - 1) / number_of_bins; // round up

            //!TODO: add split segment to segment_metadata
            seqan3::debug_stream << "split\t" << kmer_count << '\t' << 1ul << '\t' << number_of_bins << '\n';

            if (kmer_count_per_bin > max_size)
            {
                max_id = bin_id;
                max_size = kmer_count_per_bin;
            }

            bin_id += number_of_bins;

            trace_i = trace[trace_i][trace_j];
            --trace_j;
        }
        ++trace_i; // because we want the length not the index. Now trace_i == number_of_bins
        size_t const kmer_count = data->sequences[0].len;
        size_t const kmer_count_per_bin = (kmer_count + trace_i - 1) / trace_i;

        //!TODO: add split segment to segment_metadata
        seqan3::debug_stream << "split\t" << kmer_count << '\t' << 1ul << '\t' << trace_i << '\n';

        if (kmer_count_per_bin > max_size)
        {
            max_id = bin_id;
            max_size = kmer_count_per_bin;
        }

        return max_id;
    }
};

} // namespace hibf
