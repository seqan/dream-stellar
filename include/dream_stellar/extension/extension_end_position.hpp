#pragma once

#include <seqan/basic.h>

namespace dream_stellar
{
using namespace seqan2;

///////////////////////////////////////////////////////////////////////////////
// Container for storing possible end positions in extension of eps-core
template<typename TPos_>
struct ExtensionEndPosition {
    using TPosition = TPos_;
    using TCoordinate = Pair<TPosition>;

    TPosition length;
    TCoordinate coord;

    ExtensionEndPosition():
        length(0), coord(TCoordinate(0,0)) {}

    ExtensionEndPosition(TPosition len, TPosition row, TPosition col):
        length(len), coord(TCoordinate(row, col)) {}
};

} // namespace dream_stellar
