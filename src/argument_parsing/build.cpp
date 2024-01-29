#include <valik/argument_parsing/build.hpp>

namespace valik::app
{

void init_build_parser(sharg::parser & parser, build_arguments & arguments)
{
    init_shared_meta(parser);
    parser.add_positional_option(arguments.bin_file,
                                 sharg::config{.description = "File containing one file per line per bin when building from clustered sequences. "
                                                              "Input sequence file when building from overlapping segments.",
                                 .validator = sharg::input_file_validator{}});
    parser.add_option(arguments.out_path,
                      sharg::config{.short_id = '\0',
                      .long_id = "output",
                      .description = "Provide an output filepath.",
                      .required = true,
                      .validator = sharg::output_file_validator{sharg::output_file_open_options::open_or_create, {}}});
    parser.add_option(arguments.error_rate,
                      sharg::config{.short_id = 'e',
                      .long_id = "error-rate",
                      .description = "Choose the upper bound for the maximum allowed error rate of a local match.",
                      .validator = sharg::arithmetic_range_validator{0.0f, 0.1f}});
    parser.add_option(arguments.size,
                      sharg::config{.short_id = '\0',
                      .long_id = "size",
                      .description = "Choose the size of the resulting IBF.",
                      .required = true,
                      .validator = size_validator{"\\d+\\s{0,1}[k,m,g,t,K,M,G,T]"}});
    parser.add_flag(arguments.compressed,
                    sharg::config{.short_id = '\0',
                    .long_id = "compressed",
                    .description = "Build a compressed IBF."});
    parser.add_option(arguments.ref_meta_path,
                    sharg::config{.short_id = '\0',
                    .long_id = "ref-meta",
                    .description = "Path to reference metadata table created by valik split. "
                                   "Provide reference metadata to create the IBF "
                                   "from reference segments instead of a clustered database.",
                    .validator = sharg::input_file_validator{}});
    parser.add_option(arguments.threads,
                    sharg::config{.short_id = '\0',
                    .long_id = "threads",
                    .description = "Choose the number of threads.",
                    .validator = positive_integer_validator{}});
    parser.add_flag(arguments.fast,
                      sharg::config{.short_id = '\0',
                      .long_id = "fast",
                      .description = "Build the index in fast mode when few false negatives can be tolerated in the following search."});
    parser.add_flag(arguments.verbose,
                    sharg::config{.short_id = '\0',
                    .long_id = "verbose",
                    .description = "Print verbose output.",
                    .advanced = true});
    
    /////////////////////////////////////////
    // Advanced options
    /////////////////////////////////////////
    parser.add_option(arguments.window_size,
                      sharg::config{.short_id = '\0',
                      .long_id = "window",
                      .description = "Choose the window size.",
                      .advanced = true,
                      .validator = positive_integer_validator{}});
    parser.add_option(arguments.kmer_size,
                      sharg::config{.short_id = '\0',
                      .long_id = "kmer",
                      .description = "Choose the kmer size.",
                      .advanced = true,
                      .validator = sharg::arithmetic_range_validator{1, 32}});
    parser.add_option(arguments.hash,
                      sharg::config{.short_id = '\0',
                      .long_id = "hash",
                      .description = "Choose the number of hashes.",
                      .advanced = true,
                      .validator = sharg::arithmetic_range_validator{1, 5}});
}

void run_build(sharg::parser & parser)
{
    build_arguments arguments{};
    init_build_parser(parser, arguments);
    try_parsing(parser);

    // ==========================================
    // Process bin_path:
    // if building from clustered sequences each line in input corresponds to a bin
    // if building from overlapping segments all sequences in one reference file
    // ==========================================
    auto sequence_file_validator{bin_validator{}.sequence_file_validator};

    // build from reference clusters
    if (arguments.ref_meta_path.empty())
    {
        std::ifstream istrm{arguments.bin_file};
        std::string line;

        while (std::getline(istrm, line))
        {
            if (!line.empty())
            {
                sequence_file_validator(line);
                arguments.bin_path.emplace_back(std::vector<std::string>{line});
            }
        }
        arguments.bins = arguments.bin_path.size();
    }
    // build from reference segments
    else
    {
        metadata meta(arguments.ref_meta_path);
        arguments.bins = meta.seg_count;
        sequence_file_validator(arguments.bin_file);
        std::string bin_string{arguments.bin_file.string()};
        arguments.bin_path.emplace_back(std::vector<std::string>{bin_string});

        if (!parser.is_option_set("kmer") && !parser.is_option_set("window"))
        {
            // ==========================================
            // Parameter deduction
            // ==========================================
            auto space = param_space();
            std::vector<kmer_attributes> attr_vec;
            if (!read_fn_confs(attr_vec))
                precalc_fn_confs(attr_vec);

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
                std::cout << "kmer size " << best_params.k << '\n';

                find_thresholds_for_kmer_size(space, meta, attr_vec[best_params.k - std::get<0>(space.kmer_range)], arguments.error_rate);
            }
        }
    }

    // ==========================================
    // Various checks.
    // ==========================================
    if (parser.is_option_set("kmer")){
        arguments.shape = seqan3::shape{seqan3::ungapped{arguments.kmer_size}};
        arguments.shape_weight = arguments.shape.count();
    }

    if (parser.is_option_set("window"))
    {
        if (arguments.kmer_size > arguments.window_size)
            throw sharg::parser_error{"The k-mer size cannot be bigger than the window size."};
    }
    else
    {
        if (arguments.fast)
            arguments.window_size = arguments.shape.size() + 2;
        else
            arguments.window_size = arguments.shape.size();
    }

    try
    {
        sharg::output_file_validator{sharg::output_file_open_options::open_or_create}(arguments.out_path);
    }
    catch (sharg::parser_error const & ext)
    {
        std::cerr << "[Error] " << ext.what() << '\n';
        std::exit(-1);
    }

    // ==========================================
    // Process --size.
    // ==========================================
    arguments.size.erase(std::remove(arguments.size.begin(), arguments.size.end(), ' '), arguments.size.end());

    size_t multiplier{};

    switch (std::tolower(arguments.size.back()))
    {
        case 't':
            multiplier = 8ull * 1024ull * 1024ull * 1024ull * 1024ull;
            break;
        case 'g':
            multiplier = 8ull * 1024ull * 1024ull * 1024ull;
            break;
        case 'm':
            multiplier = 8ull * 1024ull * 1024ull;
            break;
        case 'k':
            multiplier = 8ull * 1024ull;
            break;
        default:
            throw sharg::parser_error{"Use {k, m, g, t} to pass size. E.g., --size 8g."};
    }

    size_t size{};
    std::from_chars(arguments.size.data(), arguments.size.data() + arguments.size.size() - 1, size);
    size *= multiplier;
    arguments.bits = size / (((arguments.bins + 63) >> 6) << 6);

    // ==========================================
    // Dispatch
    // ==========================================
    valik_build(arguments);
}

} // namespace valik::app
