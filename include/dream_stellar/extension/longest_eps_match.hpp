#pragma once

#include <utility>

#include <seqan/seeds.h>

#include <dream_stellar/extension/extension_end_position.hpp>

namespace dream_stellar
{
using namespace seqan2;

///////////////////////////////////////////////////////////////////////////////
// Identifies the longest epsilon match in align from possEndsLeft and possEndsRight and sets the view positions of
// align to start and end position of the longest epsilon match
template<typename TLength, typename TSize, typename TEps, 
typename TEnd = ExtensionEndPosition<TLength>, typename TIterator = std::vector<TEnd>::const_iterator>
std::pair<TIterator, TIterator> longestEpsMatch(std::vector<ExtensionEndPosition<TLength> > const & possEndsLeft,
                                                std::vector<ExtensionEndPosition<TLength> > const & possEndsRight,
                                                TLength const alignLen,
                                                TLength const alignErr,
                                                TSize const matchMinLength,
                                                TEps const epsilon) {

    // Identify longest eps match by iterating over combinations of left and right positions
    TIterator rightIt = possEndsRight.end() - 1;
    TIterator leftIt = possEndsLeft.end() - 1;
    TIterator right = possEndsRight.begin();
    TIterator left = possEndsLeft.begin();

    /*for (int i = 0; i < length(possEndsRight); ++i) {
        std::cout << possEndsRight[i].length << "  " << possEndsRight[i].coord.i1 << "," << possEndsRight[i].coord.i2 << std::endl;
    }
    for (int i = 0; i < length(possEndsLeft); ++i) {
        std::cout << possEndsLeft[i].length << "  " << possEndsLeft[i].coord.i1 << "," << possEndsLeft[i].coord.i2 << std::endl;
    }*/

    TSize leftErr = possEndsLeft.size() - 1;

    TSize minLength = matchMinLength;
    bool found = false;
    // DELTA is used below against floating point rounding errors.
    double const DELTA = 0.000001;

    while (leftIt >= possEndsLeft.begin()) {
        TSize totalLen = (*leftIt).length + alignLen + (*rightIt).length;
        if (totalLen < minLength) break;
        TSize totalErr = leftErr + alignErr + possEndsRight.size() - 1;
        while (rightIt >= possEndsRight.begin()) {
            totalLen = (*leftIt).length + alignLen + (*rightIt).length;
            if (totalLen < minLength) break;
            if ((TEps)totalErr/(TEps)totalLen < epsilon + DELTA) {
                right = rightIt;
                left = leftIt;
                //std::cout << totalLen << std::endl;
                minLength = totalLen;
                found = true;
                break;
            }
            --rightIt;
            --totalErr;
        }
        rightIt = possEndsRight.end() - 1;
        --leftIt;
        --leftErr;
    }

    if (found)
        return std::pair<TIterator, TIterator>(left, right);
    else
        return std::pair<TIterator, TIterator>(possEndsLeft.end(),possEndsRight.end());
}

} // namespace dream_stellar
