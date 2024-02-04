#include <valik/split/split.hpp>

namespace valik::app
{

/**
 * @brief Function that divides reference or query database into partially overlapping segments.
 *
 * @param arguments Command line arguments.
 */
void valik_split(split_arguments & arguments)
{
    if (arguments.split_index)
        arguments.seg_count = adjust_bin_count(arguments.seg_count_in);
    else
        arguments.seg_count = arguments.seg_count_in;

    metadata meta(arguments);
    meta.to_file(arguments.meta_out);

    // ==========================================
    // Parameter deduction
    // ==========================================
    auto space = param_space();
    std::vector<kmer_attributes> attr_vec;
    if (!read_fn_confs(attr_vec))
        precalc_fn_confs(attr_vec);
    
    if (arguments.split_index)
    {
        size_t errors = meta.segment_overlap() * arguments.error_rate;   
        filtering_request request(errors, meta.segment_overlap(), meta.total_len, meta.seg_count);
        auto best_params = get_best_params(space, request, attr_vec);
        arguments.kmer_size = best_params.k;

        if (arguments.verbose)
        {
            std::cout << "Build index for:\n";
            std::cout << "db length " << meta.total_len << "bp\n";
            std::cout << "min local match length " << meta.segment_overlap() << "bp\n";
            std::cout << "max error rate " << arguments.error_rate << "\n";
            std::cout << "kmer size " << std::to_string(arguments.kmer_size) << '\n';
    
            find_thresholds_for_kmer_size(space, meta, attr_vec[best_params.k - std::get<0>(space.kmer_range)], arguments.error_rate);
        }
    }
    else
    {
        if (kmer_lemma_threshold(arguments.pattern_size, (size_t) arguments.kmer_size, (size_t) arguments.errors) <= 1)
        {
            metadata ref_meta = metadata(arguments.ref_meta_path);
            std::cout.precision(3);
            std::cout << "Can not search database with an exact k-mer lemma threshold with parameters\n";
            std::cout << "min local match length " << arguments.pattern_size << "bp\n";
            std::cout << "error rate " << arguments.error_rate << "\n";
            std::cout << "kmer size " << std::to_string(arguments.kmer_size) << '\n';

            std::cout << "Applying heuristic threshold\n";
            std::cout << "use threshold " << find_threshold(space, ref_meta, meta, arguments, attr_vec[arguments.kmer_size - std::get<0>(space.kmer_range)]);
        }
    }

    if (arguments.write_out)
    {
        if (arguments.split_index)
            write_reference_segments(meta, arguments.meta_out);
        else
            write_query_segments(meta, arguments.meta_out);
    }
}

} // namespace valik::app
