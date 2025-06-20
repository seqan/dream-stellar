#include <valik/split/write_seg_sequences.hpp>

namespace valik
{

using sequence_file_t = seqan3::sequence_file_input<dna4_traits, seqan3::fields<seqan3::field::seq>>;

using types = seqan3::type_list<std::span<seqan3::dna4>, std::string>;
using fields = seqan3::fields<seqan3::field::seq, seqan3::field::id>;
using sequence_record_type = seqan3::sequence_record<types, fields>;

void write_reference_segments(metadata & reference_metadata,
                              std::filesystem::path const & ref_path)
{
    std::filesystem::path seg_path_file = ref_path;
    seg_path_file.replace_filename("seg_files.txt");

    std::ofstream file_paths_out;
    file_paths_out.open(seg_path_file);

    size_t i = 0;
    for (auto && [seq] : sequence_file_t{ref_path})
    {
        for (auto & seg : reference_metadata.segments_from_ind(i))
        {
            std::filesystem::path seg_file = ref_path;
            std::filesystem::path seg_stem = seg_file.stem();
            seg_stem += "_";
            seg_stem += std::to_string(seg.id);
            seg_stem += seg_file.extension();
            seg_file.replace_filename(seg_stem);
            file_paths_out << seg_file.string() << '\n';

            std::string id{seg.unique_id()};
            std::span<seqan3::dna4> seq_span{seq.data() + seg.start, seg.len};
            assert(seq_span.size() == seg.len);

            seqan3::sequence_file_output seg_out{seg_file};

            sequence_record_type record{seq_span, std::move(id)};
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

    size_t i = 0;
    for (auto && [seq] : sequence_file_t{query_path})
    {
        for (auto & seg : query_metadata.segments_from_ind(i))
        {
            std::string id{seg.unique_id()};
            std::span<seqan3::dna4> seq_span{seq.data() + seg.start, seg.len};
            assert(seq_span.size() == seg.len);

            sequence_record_type record{seq_span, std::move(id)};
            seg_out.push_back(record);
        }
        i++;
    }
}

} // namespace valik
