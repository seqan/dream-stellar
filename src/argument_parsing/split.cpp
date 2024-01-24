#include <seqan3/core/debug_stream.hpp>

#include <valik/argument_parsing/split.hpp>
#include <valik/split/split.hpp>

namespace valik::app
{

void init_split_parser(sharg::parser & parser, split_arguments & arguments)
{
    init_shared_meta(parser);
    parser.add_positional_option(arguments.seq_file,
                      sharg::config{.description = "File containing database sequences.",
                      .validator = sharg::input_file_validator{}});
    parser.add_option(arguments.meta_out,
                      sharg::config{.short_id = 'o',
                      .long_id = "out",
                      .description = "Please provide a valid path to the database metadata output.",
                      .validator = sharg::output_file_validator{sharg::output_file_open_options::open_or_create}});
    parser.add_option(arguments.overlap,
                      sharg::config{.short_id = '\0',
                      .long_id = "overlap",
                      .description = "Choose how much consecutive segments overlap.",
                      .validator = positive_integer_validator{true}});
    parser.add_option(arguments.seg_count_in,
                      sharg::config{.short_id = 'n',
                      .long_id = "seg-count",
                      .description = "The suggested number of database segments that might be adjusted by the split algorithm.",
                      .validator = positive_integer_validator{false}});
    parser.add_flag(arguments.split_index,
                      sharg::config{.short_id = '\0',
                      .long_id = "split-index",
                      .description = "Adjust the suggested segment count to create a multiple of 64 segments instead. This is suitable for building an IBF."});
    parser.add_flag(arguments.write_ref,
                      sharg::config{.short_id = '\0',
                      .long_id = "write-ref",
                      .description = "Write an output FASTA file for each segment.",
                      .advanced = true});
    parser.add_flag(arguments.write_query,
                      sharg::config{.short_id = '\0',
                      .long_id = "write-query",
                      .description = "Write segments into a single output FASTA file.",
                      .advanced = true});

}

void run_split(sharg::parser & parser)
{
    split_arguments arguments{};
    init_split_parser(parser, arguments);
    try_parsing(parser);

    // ==========================================
    // Dispatch
    // ==========================================
    std::string outfile = "outfile.tsv";
    write_precalc_fn_confs(outfile);

    auto attribute_vec = read_fn_confs(outfile);
    auto space = param_space();

    filtering_request request(4, arguments.overlap, arguments., arguments.);
    get_best_params(space, request, attribute_vec);


    // ==========================================
    // Dispatch
    // ==========================================
    valik_split(arguments);
}

} // namespace valik::app
