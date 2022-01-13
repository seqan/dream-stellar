void run_split()
{    
    size_t overlap = 150; // Should this be minimum local match length or read length?

    // Constraints for reasonably sized segments
    size_t min_nr_bins = 64; // IBF should have at least this many bins to allow to be concurrent "enough"
    uint32_t min_bin_len = 3 * 10e6; // segments should not be "too short"

    // Linear scan over reference file to extract metadata
    std::string filename = "/home/evelin/metagenomics/test-dream-stellar/read-mapping/dmel.fasta";
    reference_metadata reference(filename);
    reference.print_metadata();

    // Decide on number of bins and default length of segment (last segment of a reference sequence can have different length)
    uint32_t segment_len = min_bin_len; 
    if (uint32_t(std::ceil(reference.total_len / min_nr_bins)) <= min_bin_len)
        segment_len = std::ceil(reference.total_len / min_nr_bins); // divide reference into min nr of segments

    // For each segment assign start, length and bin number
    reference_segments segments(segment_len, overlap, reference.sequences);
    segments.print_metadata();

/*
    seqan3::sequence_file_input fin{"/home/evelin/metagenomics/test-dream-stellar/read-mapping/dmel.fasta"};

    for (record : fin)
    { // TODO: need to match record to only relevant segments!!
        for ([seg, bin_nr] : seqan3::views::zip(seg_vec, std::views::iota(0u)))
        {
        auto v = record | seqan3::views::chunk(seg.len);

        // add all hashes in v to IBF bin with the corresponding bin_nr        
        }
    }
*/  
}
