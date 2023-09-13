#include <valik/split/write_seg_sequences.hpp>

namespace valik
{

using sequence_file_t = seqan3::sequence_file_input<dna4_traits, seqan3::fields<seqan3::field::seq>>;

using types = seqan3::type_list<std::vector<seqan3::dna4>, std::string>;
using fields = seqan3::fields<seqan3::field::seq, seqan3::field::id>;
using sequence_record_type = seqan3::sequence_record<types, fields>;

void write_reference_segments(metadata & reference_metadata,
                              std::filesystem::path const & ref_path)
{
    std::filesystem::path seg_path_file = ref_path;
    seg_path_file.replace_filename("seg_files.txt");

    std::ofstream file_paths_out;
    file_paths_out.open(seg_path_file);

    int i = 0;
    for (auto && [seq] : sequence_file_t{ref_path})
    {
        // get the underlying sequence
        auto is_segment_sequence = [&](metadata::segment_stats & seg) {return reference_metadata.sequences.at(i).ind == seg.seq_ind;};
        for (auto & seg : reference_metadata.segments | std::views::filter(is_segment_sequence))
        {
            std::filesystem::path seg_file = ref_path;
            std::filesystem::path seg_stem = seg_file.stem();
            seg_stem += "_";
            seg_stem += std::to_string(seg.id);
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

void write_query_segments(metadata & query_metadata,
                          std::filesystem::path const & query_path)
{
    std::filesystem::path seg_out_path = query_path;
    seg_out_path.replace_extension("segments.fasta");
    seqan3::sequence_file_output seg_out{seg_out_path};

    int i = 0;
    for (auto && [seq] : sequence_file_t{query_path})
    {
        // get the underlying sequence
        auto is_segment_sequence = [&](metadata::segment_stats & seg) {return query_metadata.sequences.at(i).ind == seg.seq_ind;};
        for (auto & seg : query_metadata.segments | std::views::filter(is_segment_sequence))
        {
            std::string id{seg.unique_id()};
            seqan3::dna4_vector seg_sequence(&seq[seg.start], &seq[seg.start+seg.len]);
            assert(seg_sequence.size() == seg.len);

            sequence_record_type record{std::move(seg_sequence), std::move(id)};
            seg_out.push_back(record);
        }
        i++;
    }
}

} // namespace valik
