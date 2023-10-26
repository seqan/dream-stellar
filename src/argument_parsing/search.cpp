#include <seqan3/io/views/async_input_buffer.hpp>
#include <seqan3/core/debug_stream.hpp>

#include <valik/argument_parsing/search.hpp>
#include <valik/index.hpp>
#include <valik/search/search.hpp>

namespace valik::app
{

void init_search_parser(sharg::parser & parser, search_arguments & arguments)
{
    init_shared_meta(parser);
    parser.add_option(arguments.index_file,
                      sharg::config{.short_id = '\0',
                      .long_id = "index",
                      .description = "Provide a valid path to an IBF.",
                      .required = true,
                      .validator = sharg::input_file_validator{}});
    parser.add_option(arguments.query_file,
                      sharg::config{.short_id = '\0',
                      .long_id = "query",
                      .description = "Provide a path to the query file.",
                      .required = true,
                      .validator = sharg::input_file_validator{{"fasta", "fa", "fq", "fastq"}}});
    parser.add_option(arguments.out_file,
                      sharg::config{.short_id = '\0',
                      .long_id = "output",
                      .description = "Please provide a valid path to the output.",
                      .required = true,
                      .validator = sharg::output_file_validator{sharg::output_file_open_options::open_or_create, {"gff"}}});
    parser.add_option(arguments.error_rate,
                      sharg::config{.short_id = 'e',
                      .long_id = "error-rate",
                      .description = "Choose the maximum allowed error rate of a local match.",
                      .validator = sharg::arithmetic_range_validator{0.0f, 0.2f}});
    parser.add_option(arguments.pattern_size,
                      sharg::config{.short_id = '\0',
                      .long_id = "pattern",
                      .description = "Choose the minimium length of a local alignment. Default: half of first query sequence."});
    parser.add_flag(arguments.fast,
                      sharg::config{.short_id = '\0',
                      .long_id = "fast",
                      .description = "Execute the search in fast mode when few false negatives can be tolerated."});
    parser.add_flag(arguments.compressed,
                    sharg::config{.short_id = '\0',
                    .long_id = "compressed",
                    .description = "Build a compressed IBF."});
    parser.add_flag(arguments.write_time,
                    sharg::config{.short_id = '\0',
                    .long_id = "time",
                    .description = "Write runtime log file.",
                    .advanced = true});
    parser.add_flag(arguments.verbose,
                    sharg::config{.short_id = '\0',
                    .long_id = "verbose",
                    .description = "Print verbose output.",
                    .advanced = true});
    parser.add_option(arguments.ref_meta_path,
                    sharg::config{.short_id = '\0',
                    .long_id = "ref-meta",
                    .description = "Path to reference metadata file created by split.",
                    .validator = sharg::input_file_validator{}});
    parser.add_option(arguments.query_meta_path,
                    sharg::config{.short_id = '\0',
                    .long_id = "query-meta",
                    .description = "Path to query genome metadata for finding all local alignment between two long sequences.",
                    .validator = sharg::input_file_validator{}});
    parser.add_flag(arguments.distribute,
                    sharg::config{.short_id = '\0',
                    .long_id = "distribute",
                    .description = "Launch parallel Stellar instances each of them with independent memory."});
    parser.add_option(arguments.threads,
                    sharg::config{.short_id = '\0',
                    .long_id = "threads",
                    .description = "Choose the number of threads.",
                    .validator = positive_integer_validator{}});
    
    /////////////////////////////////////////
    // Advanced options
    /////////////////////////////////////////
    parser.add_flag(arguments.cache_thresholds,
                    sharg::config{.short_id = '\0',
                    .long_id = "cache-thresholds",
                    .description = "Stores the computed thresholds with an unique name next to the index. In the next search call "
                                   "using this option, the stored thresholds are re-used.\n"
                                   "Two files are stored:\n"
                                   "\\fBthreshold_*.bin\\fP: Depends on pattern, window, kmer/shape, errors, and tau.\n"
                                   "\\fBcorrection_*.bin\\fP: Depends on pattern, window, kmer/shape, p_max, and fpr.", 
                    .advanced = true});
    parser.add_option(arguments.tau,
                      sharg::config{.short_id = '\0',
                      .long_id = "tau",
                      .description = "Used in the dynamic thresholding. The higher tau, the lower the threshold.",
                      .advanced = true,
                      .validator = sharg::arithmetic_range_validator{0, 1}});
    parser.add_option(arguments.threshold,
                      sharg::config{.short_id = '\0',
                      .long_id = "threshold",
                      .description = "If set, this threshold is used instead of the probabilistic models.",
                      .advanced = true,
                      .validator = sharg::arithmetic_range_validator{0, 1}});
    parser.add_option(arguments.p_max,
                      sharg::config{.short_id = '\0',
                      .long_id = "p_max",
                      .description = "Used in the dynamic thresholding. The higher p_max, the lower the threshold.",
                      .advanced = true,
                      .validator = sharg::arithmetic_range_validator{0, 1}});
    parser.add_option(arguments.overlap,
                      sharg::config{.short_id = '\0',
                      .long_id = "overlap",
                      .description = "Choose how much sequential patterns overlap. "
                                     "This determines how many potential matches are skipped in prefiltering."
                                     "(pattern_size - 1) considers all potential matches.", 
                      .advanced = true});
    parser.add_option(arguments.cart_max_capacity,
                    sharg::config{.short_id = '\0',
                    .long_id = "cart_max_capacity",
                    .description = "Number of elements to be stored in a single cart before it is sent for processing.", 
                    .advanced = true});
    parser.add_option(arguments.max_queued_carts,
                    sharg::config{.short_id = '\0',
                    .long_id = "max_queued_carts",
                    .description = "Maximal number of carts that are full and are waiting to be processed.",
                    .advanced = true});
    parser.add_option(arguments.disableThresh,
                    sharg::config{.short_id = '\0',
                    .long_id = "disableThresh",
                    .description = "STELLAR: Maximal number of verified SWIFT filter matches before disabling verification for one query sequence.",
                    .advanced = true,
                    .validator = sharg::arithmetic_range_validator{1, 10000}});
    parser.add_option(arguments.compactThresh,
                    sharg::config{.short_id = 's',
                    .long_id = "sortThresh",
                    .description = "STELLAR: Number of matches triggering removal of duplicates. Choose a smaller value for saving space.", 
                    .advanced = true});
    parser.add_option(arguments.qGram,
                    sharg::config{.short_id = 'q',
                    .long_id = "stellar-kmer",
                    .description = "STELLAR: Length of the q-grams in the SWIFT algorithm.",
                    .advanced = true,
                    .validator = sharg::arithmetic_range_validator{1, 32}});
    parser.add_option(arguments.qgramAbundanceCut,
                    sharg::config{.short_id = 'c',
                    .long_id = "abundanceCut",
                    .description = "STELLAR: k-mer overabundance cut ratio.",
                    .advanced = true,
                    .validator = sharg::arithmetic_range_validator{0, 1}});
    parser.add_option(arguments.maxRepeatPeriod,
                    sharg::config{.short_id = '\0',
                    .long_id = "repeatPeriod",
                    .description = "STELLAR: Maximal period of low complexity repeats to be filtered.",
                    .advanced = true,
                    .validator = sharg::arithmetic_range_validator{1, 32}});
    parser.add_option(arguments.minRepeatLength,
                    sharg::config{.short_id = '\0',
                    .long_id = "repeatLength",
                    .description = "STELLAR: Minimal length of low complexity repeats to be filtered.",
                    .advanced = true,
                    .validator = sharg::arithmetic_range_validator{1u, std::numeric_limits<uint32_t>::max()}});
    parser.add_option(arguments.xDrop,
                    sharg::config{.short_id = 'x',
                    .long_id = "xDrop",
                    .description = "STELLAR: Maximal x-drop for extension.", 
                    .advanced = true});
    parser.add_option(arguments.strVerificationMethod,
                    sharg::config{.short_id = '\0',
                    .long_id = "verification",
                    .description = "STELLAR: Verification strategy: exact or bestLocal or bandedGlobal.",
                    .advanced = true,
                    .validator = sharg::value_list_validator{"exact", "bestLocal", "bandedGlobal", "bandedGlobalExtend"}});
    parser.add_option(arguments.numMatches,
                    sharg::config{.short_id = 'n',
                    .long_id = "numMatches",
                    .description = "STELLAR: Maximal number of kept matches per query and database." 
                                   "If STELLAR finds more matches, only the longest ones are kept.",
                    .advanced = true});
}

void run_search(sharg::parser & parser)
{
    search_arguments arguments{};

    init_search_parser(parser, arguments);

    try_parsing(parser);

    arguments.errors = std::ceil(arguments.error_rate * arguments.pattern_size);

    // ==========================================
    // Various checks.
    // ==========================================

    sharg::input_file_validator{}(arguments.query_file);
    arguments.treshold_was_set = parser.is_option_set("threshold");

    // ==========================================
    // Read window and kmer size, and the bin paths.
    // ==========================================
    {
        std::ifstream is{arguments.index_file.string(),std::ios::binary};
        cereal::BinaryInputArchive iarchive{is};
        valik_index<> tmp{};
        tmp.load_parameters(iarchive);
        arguments.shape = tmp.shape();
        arguments.shape_size = arguments.shape.size();
        arguments.shape_weight = arguments.shape.count();
        arguments.window_size = tmp.window_size();
        arguments.compressed = tmp.compressed();
        arguments.bin_path = tmp.bin_path();
    }

    // ==========================================
    // Process --pattern.
    // ==========================================

    if (parser.is_option_set("pattern"))
    {
        if (arguments.pattern_size < arguments.window_size)
            throw sharg::validation_error{"The minimiser window cannot be bigger than the pattern."};
    }
    else

    // ==========================================
    // Set default pattern size.
    // ==========================================
    if (!arguments.pattern_size)
    {
        seqan3::sequence_file_input<dna4_traits, seqan3::fields<seqan3::field::seq>> query_in{arguments.query_file};
        for (auto & [seq] : query_in | std::views::take(1))
        {
            arguments.pattern_size = std::ranges::size(seq) / 2;
        }
    }

    // ==========================================
    // Create temporary file path for merging distributed Stellar runs.
    // ==========================================
    if (!arguments.ref_meta_path.empty())
    {
        arguments.all_matches = arguments.out_file;
        arguments.all_matches += ".preliminary";
    }

    // ==========================================
    // Check for split metadata.
    // ==========================================
    if (!arguments.distribute && arguments.ref_meta_path.empty())
        throw std::runtime_error("Provide --ref-meta to search a single genome or launch a --distribute run to search multiple reference files instead.");

    // ==========================================
    // More checks.
    // ==========================================
    if (parser.is_option_set("overlap"))
    {
        if (arguments.overlap >= arguments.pattern_size)
                throw sharg::validation_error{"The overlap size has to be smaller than the pattern size."};
    }
    else
    {
        if (arguments.fast)
            arguments.overlap = arguments.pattern_size - 2;
        else 
            arguments.overlap = arguments.pattern_size - 1;
    }

    if (arguments.numMatches > arguments.compactThresh)
        throw sharg::validation_error{"Invalid parameter values: Please choose numMatches <= sortThresh.\n"};

    // ==========================================
    // Set strict thresholding parameters for fast mode.
    // ==========================================
    if (!parser.is_option_set("tau") && arguments.fast)
        arguments.tau = 0.99999;

    if (!parser.is_option_set("p_max") && arguments.fast)
        arguments.p_max = 0.05;

    // ==========================================
    // Dispatch
    // ==========================================
    valik_search(arguments);
}

} // namespace valik::app
