#include <valik/split/split.hpp>
#include <valik/argument_parsing/build.hpp>

namespace valik::app
{

void init_build_parser(sharg::parser & parser, build_arguments & arguments)
{
    param_space space{};
    init_shared_meta(parser);

    /////////////////////////////////////////
    // Split options
    /////////////////////////////////////////
    parser.add_positional_option(arguments.db_file,
                      sharg::config{.description = "File containing database sequences. If splitting --metagenome provide a text file with a list of cluster paths.",
                      .validator = sharg::input_file_validator{}});
    parser.add_option(arguments.pattern_size,
                      sharg::config{.short_id = '\0',
                      .long_id = "pattern",
                      .description = "Choose how much consecutive segments overlap. This is the minimum length of a local alignment.",
                      .validator = sharg::arithmetic_range_validator{10u, 1000u}});
    parser.add_option(arguments.error_rate,
                      sharg::config{.short_id = 'e',
                      .long_id = "error-rate",
                      .description = "Choose the upper bound for the maximum allowed error rate of a local match.",
                      .validator = sharg::arithmetic_range_validator{0.0f, 0.2f}});
    parser.add_option(arguments.fpr,
                      sharg::config{.short_id = '\0',
                      .long_id = "fpr",
                      .description = "False positive rate of IBF.",
                      .validator = sharg::arithmetic_range_validator{0.0001f, 0.5f}});
    parser.add_option(arguments.kmer_size,
                      sharg::config{.short_id = 'k',
                      .long_id = "kmer",
                      .description = "Choose the ungapped kmer size.",
                      .validator = sharg::arithmetic_range_validator{space.min_k(), space.max_k()}});
    parser.add_option(arguments.shape_str,
                      sharg::config{.short_id = 's',
                      .long_id = "shape",
                      .description = "Choose the kmer shape. E.g 15-mer with two gaps: 111110111011111.",
                      .validator = sharg::regex_validator{"[01]+"}});
    parser.add_option(arguments.seg_count_in,
                      sharg::config{.short_id = 'n',
                      .long_id = "seg-count",
                      .description = "The number of database segments should be a multiple of 64.",
                      .validator = positive_integer_validator{false}});
    parser.add_flag(arguments.metagenome,
                      sharg::config{.short_id = '\0',
                      .long_id = "metagenome",
                      .description = "Split a clustered metagenome database. Reference input is a list of cluster paths"});

    parser.add_option(arguments.out_path,
                      sharg::config{.short_id = 'o',
                      .long_id = "output",
                      .description = "Provide an output filepath."});
    parser.add_option(arguments.threads,
                    sharg::config{.short_id = '\0',
                    .long_id = "threads",
                    .description = "Choose the number of threads.",
                    .validator = positive_integer_validator{}});
    parser.add_flag(arguments.fast,
                      sharg::config{.short_id = '\0',
                      .long_id = "fast",
                      .description = "Build the index in fast mode when few false negatives can be tolerated in the following search."});
    parser.add_flag(arguments.manual_parameters,
                      sharg::config{.short_id = '\0',
                      .long_id = "without-parameter-tuning",
                      .description = "Do not read parameters from metadata.",
                      .advanced = true});
    parser.add_flag(arguments.split_only,
                      sharg::config{.short_id = '\0',
                      .long_id = "split-only",
                      .description = "Do not build IBF.",
                      .advanced = true});
    parser.add_option(arguments.information_content,
                      sharg::config{.short_id = '\0',
                      .long_id = "inf-cont",
                      .description = "Effective sequence size constant.",
                      .advanced = true});
    /////////////////////////////////////////
    // Advanced options
    /////////////////////////////////////////
    parser.add_flag(arguments.write_out,
                      sharg::config{.short_id = '\0',
                      .long_id = "write-out",
                      .description = "Write an output FASTA file for each reference segment or write all query segments into a single output FASTA file.",
                      .advanced = true});
    parser.add_option(arguments.window_size,
                      sharg::config{.short_id = 'w',
                      .long_id = "window",
                      .description = "Choose the window size.",
                      .advanced = true,
                      .validator = positive_integer_validator{}});
    parser.add_option(arguments.hash,
                      sharg::config{.short_id = '\0',
                      .long_id = "hash",
                      .description = "Choose the number of hashes.",
                      .advanced = true,
                      .validator = sharg::arithmetic_range_validator{1, 5}});
    parser.add_option(arguments.size,
                      sharg::config{.short_id = '\0',
                      .long_id = "size",
                      .description = "Choose the size of the resulting IBF.",
                      .advanced = true,
                      .validator = size_validator{"\\d+\\s{0,1}[k,m,g,t,K,M,G,T]"}});
    parser.add_flag(arguments.verbose,
                    sharg::config{.short_id = '\0',
                    .long_id = "verbose",
                    .description = "Print verbose output.",
                    .advanced = true});    
    
    parser.add_subsection("Processing options");
    parser.add_option(arguments.kmer_count_min_cutoff,
                      sharg::config{.short_id = '\0',
                                    .long_id = "kmer-count-min",
                                    .description = "Only store k-mers with at least (>=) x occurrences. "
                                                   "Mutually exclusive with --use-filesize-dependent-cutoff.",
                                    .validator = sharg::arithmetic_range_validator{0, 254}});
    parser.add_option(arguments.kmer_count_max_cutoff,
                      sharg::config{.short_id = '\0',
                                    .long_id = "kmer-count-max",
                                    .description = "Only store k-mers with no more than (<=) x occurrences. "
                                                   "Mutually exclusive with --use-filesize-dependent-cutoff.",
                                    .validator = sharg::arithmetic_range_validator{1, 254}});
}

void run_build(sharg::parser & parser)
{
    build_arguments arguments{};
    init_build_parser(parser, arguments);
    try_parsing(parser);

    if (parser.is_option_set("kmer"))
    {
        if (parser.is_option_set("shape"))
        {
            throw sharg::parser_error{"Arguments --kmer and --shape are mutually exclusive."};
        }
        else
        {
            arguments.shape = seqan3::shape{seqan3::ungapped(arguments.kmer_size)};
            arguments.shape_str = std::string(arguments.kmer_size, '1');
            arguments.shape_weight = arguments.kmer_size;
        }
    }

    if (parser.is_option_set("shape"))
    {
        uint64_t bin_shape{};
        std::from_chars(arguments.shape_str.data(), arguments.shape_str.data() + arguments.shape_str.size(), bin_shape, 2);
        arguments.shape = seqan3::shape(seqan3::bin_literal{bin_shape});
        arguments.kmer_size = arguments.shape.size();
        arguments.shape_weight = arguments.shape.count();
    }

    arguments.errors = std::ceil(arguments.error_rate * arguments.pattern_size);
    // ==========================================
    // Process bin_path:
    // if building from clustered sequences each line in input corresponds to a bin
    // if building from overlapping segments all sequences in one reference file
    // ==========================================
    auto sequence_file_validator{bin_validator{}.sequence_file_validator};

    if (arguments.metagenome)
    {
        std::ifstream istrm{arguments.db_file};
        std::string bin_path;
        while (std::getline(istrm, bin_path))
        {
            if (!bin_path.empty())
            {
                sequence_file_validator(bin_path);
                arguments.bin_path.emplace_back(bin_path);
            }
        }
    }
    else
    {
        sequence_file_validator(arguments.db_file);
        std::string bin_string{arguments.db_file.string()};
        arguments.bin_path.emplace_back(bin_string);
    }

    if (!parser.is_option_set("output"))
    {
        arguments.out_path = arguments.db_file;
        arguments.out_path.replace_extension("index");
    }
    sharg::output_file_validator{sharg::output_file_open_options::open_or_create}(arguments.out_path);
    
    arguments.ref_meta_path = arguments.out_path;
    arguments.ref_meta_path.replace_extension("bin");

    if ((parser.is_option_set("seg-count") || parser.is_option_set('n')) && !arguments.manual_parameters)
    {
        if (arguments.seg_count_in % 64 != 0)
        {
            std::cerr << "WARNING: seg count will be adjusted to the next multiple of 64. "
                      << "Set --without-parameter-tuning to force manual input.\n";
        }
    }

    // ==========================================
    // Dispatch split
    // ==========================================
    if (arguments.manual_parameters)
    {
        // use user parameter input
        arguments.seg_count = arguments.seg_count_in;
    }
    else
    {
        // bin count is multiple of 64
        arguments.seg_count = adjust_bin_count(arguments.seg_count_in);
    }

    metadata meta(arguments);
    meta.save(arguments.ref_meta_path);

    if (arguments.verbose)
    {
        std::cout << "\n-----------Preprocessing reference database-----------\n";
        std::cout << "database size " << meta.total_len << "bp\n";
        std::cout << "segment count " << meta.seg_count << '\n';
        std::cout << "segment len " << std::to_string((uint64_t) std::round(meta.total_len / (double) meta.seg_count)) << "bp\n";
    }


    // ==========================================
    // Parameter deduction
    // ==========================================
    auto space = param_space();
    fn_confs fn_attr = fn_confs(space);

    search_pattern pattern(arguments.errors, arguments.pattern_size);
    if (arguments.verbose)
    {
        std::cout << "\n-----------Local match definition-----------\n";
        std::cout << "min length " << arguments.pattern_size << "bp\n";
        std::cout << "max error rate " << arguments.error_rate << '\n';
    }
        
    if (arguments.kmer_size == std::numeric_limits<uint8_t>::max())
    {
        auto deduced_ungapped = get_best_params(pattern, meta, fn_attr, arguments.verbose);
        if (arguments.verbose)
            std::cerr << "Deduced k-mer size: " << (int) deduced_ungapped.kmer.size() << '\n';

        auto best_params = deduced_ungapped.get_equivalent_gapped();

        arguments.kmer_size = best_params.kmer.size();
        arguments.shape = best_params.kmer.shape;
        arguments.shape_str = best_params.kmer.to_string();
        arguments.shape_weight = best_params.kmer.weight();
    }
    else if (arguments.shape_str.empty() && !parser.is_option_set("shape"))
    {
        auto kmer = utilities::kmer{arguments.kmer_size};
        auto input_ungapped = param_set{kmer, kmer.lemma_threshold(arguments.pattern_size, arguments.errors)};
        auto best_params = input_ungapped.get_equivalent_gapped();

        arguments.kmer_size = best_params.kmer.size();
        arguments.shape = best_params.kmer.shape;
        arguments.shape_str = best_params.kmer.to_string();
        arguments.shape_weight = best_params.kmer.weight();
    }
    
    if (!parser.is_option_set("window"))
    {
        if (arguments.fast)
        {
            arguments.window_size = arguments.kmer_size + 2;
            arguments.input_is_minimiser = true;
        }
        else
            arguments.window_size = arguments.kmer_size;
    }

    if (arguments.kmer_size > arguments.window_size)
    {
        throw sharg::parser_error{"The k-mer size cannot be bigger than the window size."};
    }

    search_kmer_profile search_profile = find_thresholds_for_kmer_size(meta, fn_attr, utilities::kmer{arguments.shape}, 
                                                                       arguments.errors, arguments.fast);
    if (arguments.verbose)
        search_profile.print();

    std::filesystem::path search_profile_file{arguments.ref_meta_path};
    search_profile_file.replace_extension("arg");
    search_profile.save(search_profile_file);

    if (arguments.write_out && !arguments.metagenome)
    {
        write_reference_segments(meta, arguments.db_file);
    }

    arguments.seg_count = meta.seg_count;

    try
    {
        arguments.out_dir = arguments.out_path.parent_path();
    }
    catch (sharg::parser_error const & ext)
    {
        std::cerr << "[Error] " << ext.what() << '\n';
        std::exit(-1);
    }

    if (!arguments.split_only)
    {
        // ==========================================
        // Process minimiser parameters for IBF size calculation.
        // ==========================================
        if (arguments.fast)
            raptor::compute_minimiser(arguments);   // requires bin_path and out_dir
    
        // ==========================================
        // Find IBF size.
        // ==========================================
        if (parser.is_option_set("size"))
        {
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
            arguments.bits = size / (((arguments.seg_count + 63) >> 6) << 6);
        }
        else 
        {
            arguments.fpr = meta.ibf_fpr;
            arguments.bits = raptor::compute_bin_size(arguments);
        }
    
        // ==========================================
        // Dispatch
        // ==========================================

        if (arguments.verbose)
        {
            std::cout << "\n-----------Building index-----------\n";
            std::cout << "IBF size " << arguments.bits << " bits\n";
            std::cout << "k-mer size " << (int) arguments.kmer_size << '\n';
            std::cout << "shape weight " << (int) arguments.shape_weight << '\n';
            std::cout << "window size " << (int) arguments.window_size << '\n';
        }
        valik_build(arguments);
    }
    else
        return;
}

} // namespace valik::app
