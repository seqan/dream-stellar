#include <seqan3/core/debug_stream.hpp>

class reference_segments {
    public: 
        class segment {
            public:
                std::string ref_id;
                uint32_t start;
                uint32_t len;
                size_t bin;

            segment(std::string id, uint32_t s, uint32_t l, size_t b) { // Constructor with parameters
                ref_id = id;
                start = s;
                len = l;
                bin = b;
            }
        };

        std::vector<segment> members;
        uint32_t default_len;

        void add_segment(std::string id, uint32_t s, uint32_t l, size_t b)
        {
            segment seg(id, s, l, b);
            members.push_back(seg);
        }

        reference_segments(uint32_t segment_len, size_t overlap, auto & reference_sequences)
        {
            default_len = segment_len;
            int i = 0;
            for (const auto & seq : reference_sequences)
            {
                uint32_t start = 0;

                // only one segment per reference sequence
                if (start + segment_len >= seq.len)
                {
                    add_segment(seq.id, start, seq.len, i);
                    i++;
                } 
                
                // many segments per reference sequence
                else 
                {
                    add_segment(seq.id, start, segment_len, i);
                    i++;
                    while (start + segment_len < seq.len)
                    {
                        start = start + segment_len - overlap;
                        add_segment(seq.id, start, segment_len, i);
                        i++;
                    }
                    add_segment(seq.id, start, seq.len - start, i);
                    i++;
                }
            }
        }

        void print_metadata()
        {
            seqan3::debug_stream << "------------------- SEGMENT METADATA -------------------" << '\n';
            seqan3::debug_stream << "(default) LENGTH: " << default_len << '\n';

            seqan3::debug_stream << "BIN" << '\t' << "REF ID" << '\t' << "START" << '\t' << "LEN" << '\n';
            for (const auto & seg : members)
            {
                seqan3::debug_stream << seg.bin << '\t' << seg.ref_id << '\t' << seg.start << '\t' << seg.len << '\n';
            }
        }
};