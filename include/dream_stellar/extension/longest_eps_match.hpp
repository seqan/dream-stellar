#pragma once

#include <seqan/seeds.h>

#include <dream_stellar/extension/extension_end_position.hpp>

namespace dream_stellar
{
using namespace seqan2;

///////////////////////////////////////////////////////////////////////////////
// Identifies the longest epsilon match in align from possEndsLeft and possEndsRight and sets the view positions of
// align to start and end position of the longest epsilon match
template<typename TLength, typename TSize, typename TEps>
Pair<typename Iterator<String<ExtensionEndPosition<TLength> > const>::Type>
longestEpsMatch(String<ExtensionEndPosition<TLength> > const & possEndsLeft,
                String<ExtensionEndPosition<TLength> > const & possEndsRight,
                TLength const alignLen,
                TLength const alignErr,
                TSize const matchMinLength,
                TEps const epsilon) {
    typedef ExtensionEndPosition<TLength>               TEnd;
    typedef typename Iterator<String<TEnd> const>::Type TIterator;

    // Identify longest eps match by iterating over combinations of left and right positions
    TIterator rightIt = end(possEndsRight) - 1;
    TIterator leftIt = end(possEndsLeft) - 1;
    TIterator right = begin(possEndsRight);
    TIterator left = begin(possEndsLeft);

    /*for (int i = 0; i < length(possEndsRight); ++i) {
        std::cout << possEndsRight[i].length << "  " << possEndsRight[i].coord.i1 << "," << possEndsRight[i].coord.i2 << std::endl;
    }
    for (int i = 0; i < length(possEndsLeft); ++i) {
        std::cout << possEndsLeft[i].length << "  " << possEndsLeft[i].coord.i1 << "," << possEndsLeft[i].coord.i2 << std::endl;
    }*/

    TSize leftErr = length(possEndsLeft) - 1;

    TSize minLength = matchMinLength;
    bool found = false;
    // DELTA is used below against floating point rounding errors.
    double const DELTA = 0.000001;

    while (leftIt >= begin(possEndsLeft)) {
        TSize totalLen = (*leftIt).length + alignLen + (*rightIt).length;
        if (totalLen < minLength) break;
        TSize totalErr = leftErr + alignErr + length(possEndsRight) - 1;
        while (rightIt >= begin(possEndsRight)) {
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
        rightIt = end(possEndsRight) - 1;
        --leftIt;
        --leftErr;
    }

    if (found)
        return Pair<TIterator>(left, right);
    else
        return Pair<TIterator>(0,0);
}

} // namespace dream_stellar
