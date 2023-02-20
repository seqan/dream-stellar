#include <valik/argument_parsing/build.hpp>
#include <valik/build/build.hpp>

#include <valik/split/reference_segments.hpp>

namespace valik::app
{

void init_build_parser(seqan3::argument_parser & parser, build_arguments & arguments)
{
    init_shared_meta(parser);
    init_shared_options(parser, arguments);
    parser.add_positional_option(arguments.bin_file,
                                 "File containing one file per line per bin when building from clustered sequences. "
                                 "Input sequence file when building from overlapping segments.",
                                 seqan3::input_file_validator{});
    parser.add_option(arguments.window_size,
                      '\0',
                      "window",
                      "Choose the window size.",
                      seqan3::option_spec::standard,
                      positive_integer_validator{});
    parser.add_option(arguments.kmer_size,
                      '\0',
                      "kmer",
                      "Choose the kmer size.",
                      seqan3::option_spec::standard,
                      seqan3::arithmetic_range_validator{1, 32});
    parser.add_option(arguments.out_path,
                      '\0',
                      "output",
                      "Provide an output filepath.",
                      seqan3::option_spec::required);
    parser.add_option(arguments.size,
                      '\0',
                      "size",
                      "Choose the size of the resulting IBF.",
                      seqan3::option_spec::required,
                      size_validator{"\\d+\\s{0,1}[k,m,g,t,K,M,G,T]"});
    parser.add_option(arguments.hash,
                      '\0',
                      "hash",
                      "Choose the number of hashes.",
                      seqan3::option_spec::standard,
                      seqan3::arithmetic_range_validator{1, 5});
    parser.add_flag(arguments.compressed,
                    '\0',
                    "compressed",
                    "Build a compressed IBF.");
    parser.add_flag(arguments.from_segments,
                    '\0',
                    "from-segments",
                    "Creates IBF from split reference database instead of reference clusters.",
                    seqan3::option_spec::standard);
    parser.add_option(arguments.seg_path,
                    '\0',
                    "seg-path",
                    "Path to segment metadata file created by split.",
                    seqan3::option_spec::standard,
                    seqan3::input_file_validator{});
    parser.add_option(arguments.ref_meta_path,
                    '\0',
                    "ref-meta",
                    "Path to reference metadata file created by split.",
                    seqan3::option_spec::standard,
                    seqan3::input_file_validator{});
}

void run_build(seqan3::argument_parser & parser)
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

    if (!arguments.from_segments)
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
    else
    {
        reference_segments seg(arguments.seg_path);
        arguments.bins = seg.members.size();
        sequence_file_validator(arguments.bin_file);
        std::string bin_string{arguments.bin_file.string()};
        arguments.bin_path.emplace_back(std::vector<std::string>{bin_string});
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
            throw seqan3::argument_parser_error{"The k-mer size cannot be bigger than the window size."};
    }
    else
        arguments.window_size = arguments.shape.size();

    try
    {
        seqan3::output_file_validator{seqan3::output_file_open_options::open_or_create}(arguments.out_path);
    }
    catch (seqan3::argument_parser_error const & ext)
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
            throw seqan3::argument_parser_error{"Use {k, m, g, t} to pass size. E.g., --size 8g."};
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
