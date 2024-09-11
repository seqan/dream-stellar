#pragma once

#include <set>
#include <cstdint>
#include <cstddef>
#include <vector>

namespace dream_stellar
{

struct DREAMOptions
{
    bool prefilteredSearch{false};  // search a subset of all reference sequences (e.g chr 1, chr 2)
    bool searchSegment{false};  // search a segment of a single reference sequence (e.g chr1:1000-3000)
    uint64_t referenceLength{0};

    // Specify the segment (and sequence) of interest.
    std::vector<size_t> binSequences;
    uint32_t segmentBegin;
    uint32_t segmentEnd;
};

} // namespace dream_stellar
