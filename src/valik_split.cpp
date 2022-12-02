#include <valik/argument_parsing/shared.hpp>
#include <valik/shared.hpp>
#include <valik/split/reference_metadata.hpp>
#include <valik/split/reference_segments.hpp>

namespace valik::app
{

//-----------------------------
//
// Divide reference database into partially overlapping segments and write metadata files.
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

    using traits_type = seqan3::sequence_file_input_default_traits_dna;
    seqan3::sequence_file_input<traits_type> fin{arguments.ref_file};

    using types = seqan3::type_list<std::vector<seqan3::dna4>, std::string>;
    using fields = seqan3::fields<seqan3::field::seq, seqan3::field::id>;
    using sequence_record_type = seqan3::sequence_record<types, fields>;

    int i = 0;
    for (auto && record : fin)
    {
        // get the relevant segments for each reference
        auto ref_seg = [&](reference_segments::segment & seg) {return reference.sequences.at(i).id == seg.ref_id;};
        for (auto & seg : segments.members | std::views::filter(ref_seg))
        {
            std::filesystem::path bin_file = arguments.ref_file;
            std::filesystem::path new_stem = bin_file.stem();
            new_stem += "_";
            new_stem += std::to_string(seg.bin);
            new_stem += bin_file.extension();
            bin_file.replace_filename(new_stem);

            std::string id{seg.ref_id + "_" + std::to_string(seg.start) + "_" + std::to_string(seg.len)};
            seqan3::dna4_vector sequence(&record.sequence()[seg.start], &record.sequence()[seg.start+seg.len]);

            seqan3::sequence_file_output fout{bin_file};

            sequence_record_type record{std::move(sequence), std::move(id)};
            fout.push_back(record);
        }
        i++;
    }
}

} // namespace valik::app
