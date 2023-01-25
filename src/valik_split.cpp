#include <valik/argument_parsing/shared.hpp>
#include <valik/shared.hpp>
#include <valik/split/reference_metadata.hpp>
#include <valik/split/reference_segments.hpp>

namespace valik::app
{

template <typename dna_t>
void write_seg_sequences(reference_metadata const & reference, reference_segments & segments, std::filesystem::path const & ref_path)
{
    using sequence_file_t = seqan3::sequence_file_input<dna4_traits, seqan3::fields<seqan3::field::seq>>;

    using types = seqan3::type_list<std::vector<dna_t>, std::string>;
    using fields = seqan3::fields<seqan3::field::seq, seqan3::field::id>;
    using sequence_record_type = seqan3::sequence_record<types, fields>;

    std::filesystem::path seg_path_file = ref_path;
    seg_path_file.replace_filename("seg_files.txt");

    std::ofstream file_paths_out;
    file_paths_out.open(seg_path_file);

    int i = 0;
    for (auto && [seq] : sequence_file_t{ref_path})
    {
        // get the relevant segments for each reference
        auto ref_seg = [&](reference_segments::segment & seg) {return reference.sequences.at(i).ind == seg.ref_ind;};
        for (auto & seg : segments.members | std::views::filter(ref_seg))
        {
            std::filesystem::path seg_file = ref_path;
            std::filesystem::path seg_stem = seg_file.stem();
            seg_stem += "_";
            seg_stem += std::to_string(seg.bin);
            seg_stem += seg_file.extension();
            seg_file.replace_filename(seg_stem);
            file_paths_out << seg_file.string() << '\n';

            std::string id{seg.unique_id()};
            seqan3::dna4_vector seg_sequence(&seq[seg.start], &seq[seg.start+seg.len]);
            assert(seg_sequence.size() == seg.len);

            seqan3::sequence_file_output seg_out{seg_file};

            sequence_record_type record{std::move(seg_sequence), std::move(id)};
            seg_out.push_back(record);
        }
        i++;
    }

    file_paths_out.close();
}

//-----------------------------
//
// Divide reference database into partially overlapping segments.
//
//-----------------------------
void valik_split(split_arguments const & arguments)
{
    // Linear scan over reference file to extract metadata
    reference_metadata reference(arguments.ref_file, true);
    reference.to_file(arguments.ref_out);

    // For each segment assign start, length and bin number
    reference_segments segments(arguments.bins, arguments.overlap, reference);
    segments.to_file(arguments.seg_out);

    if (arguments.write_seg)
        write_seg_sequences<seqan3::dna4>(reference, segments, arguments.ref_file);
}

} // namespace valik::app
