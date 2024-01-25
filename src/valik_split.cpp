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
    // Search parameter tuning
    // ==========================================
    auto space = param_space();
    std::vector<kmer_attributes> attr_vec;
    if (!read_fn_confs(attr_vec))
        precalc_fn_confs(attr_vec);

    size_t max_errors = 2;
    filtering_request request(max_errors, arguments.overlap, meta.total_len, meta.seg_count);
    get_best_params(space, request, attr_vec);

    if (arguments.write_ref)
        write_reference_segments(meta, arguments.meta_out);
    if (arguments.write_query)
        write_query_segments(meta, arguments.meta_out);
}

} // namespace valik::app
