#pragma once

#include <dream_stellar/extension/align_banded_nw_best_ends.hpp>
#include <dream_stellar/extension/extension_end_position.hpp>
#include <dream_stellar/extension/longest_eps_match.hpp>
#include <dream_stellar/utils/stellar_kernel_runtime.hpp>

#include <seqan/seeds.h>
#include <utilities/alphabet_wrapper/std/span.hpp>

namespace dream_stellar
{
using namespace seqan2;

///////////////////////////////////////////////////////////////////////////////
// returns true if align has a match at pos, otherwise false
template<typename TSource, typename TSize>
inline bool
isMatch(Align<TSource> const & align, TSize const pos) {

    if(isGap(row(align, 0), pos)) {
        return false;
    } else if(isGap(row(align, 1), pos)) {
        return false;
    } else if(row(align, 0)[pos] != row(align, 1)[pos]) {
        return false;
    } else {
        return true;
    }
}

///////////////////////////////////////////////////////////////////////////////
// Computes possible end positions of an eps-match in a given alignment.
template<typename TSource, typename TPos>
void
_fillGapsString(Align<TSource> const & align,
                String<Triple<TPos, TPos, TPos> > & gaps) {
    typedef Triple<TPos, TPos, TPos> TGapInfo;
    TPos totalErrors = 0;
    typename Row<Align<TSource> >::Type row0 = row(align, 0);
    TPos i = 0;
    TPos endPos = length(row0);
    TPos gapBegin = i;

    // append gap starting at beginPosition (also if its length is 0!)
    while(i < endPos && !isMatch(align, i)) {
        ++i;
        ++totalErrors;
    }
    appendValue(gaps, TGapInfo(gapBegin, i, totalErrors));

    // iterate over alignment and append gaps
    while (i < endPos) {
        // skip matches
        while(i < endPos && isMatch(align, i)) {
            ++i;
        }
        gapBegin = i;
        // skip and count mismatches/indels
        while(i < endPos && !isMatch(align, i)) {
            ++i;
            ++totalErrors;
        }
        appendValue(gaps, TGapInfo(gapBegin, i, totalErrors));
    }
    /*for(unsigned l = 0; l < length(gaps); ++l) {
        std::cout << gaps[l].i1 << "  " << gaps[l].i2 << "  " << gaps[l].i3 << std::endl;
    }*/
}

///////////////////////////////////////////////////////////////////////////////
// Checks the error rate of the fragment between end of left and start of right.
template<typename TPos, typename TFloat>
inline bool
_isEpsMatch(Triple<TPos, TPos, TPos> const & left,
           Triple<TPos, TPos, TPos> const & right,
           TFloat const eps) {
    // compute mismatches/indels and length
    TPos errors = right.i3 - left.i3 - (right.i2 - right.i1);
    TPos len = right.i1 - left.i2;

    // check error rate
    double const DELTA = 0.000001;  // Small delta against floating point precision problems.
    return errors/(TFloat)(len) <= eps + DELTA;
}

///////////////////////////////////////////////////////////////////////////////
// Identifies the longest epsilon match in align and sets the view positions of
// align to start and end position of the longest epsilon match
template<typename TSource, typename TSize, typename TFloat>
bool
longestEpsMatch(Align<TSource> & align,
                TSize const matchMinLength,
                TFloat const epsilon) {
    // Preprocessing: compute and store gaps and lengths
    // A gap is a triple of gap begin position, gap end position, and total number of errors in sequence from begin
    //   to end position of this gap.
    typedef typename Position<Align<TSource> >::Type TPosition;
    typedef String<Triple<TPosition, TPosition, TPosition> > TGapsString;
    TGapsString gaps;
    _fillGapsString(align, gaps);

    // Identify longest eps match by iterating over combinations of left and right positions
    typename Iterator<TGapsString >::Type rightIt = end(gaps) - 1;
    typename Iterator<TGapsString >::Type leftIt = begin(gaps);

    TPosition beginPos = 0;
    TPosition endPos = 0;
    TSize minLength = matchMinLength - 1;

    while ((*leftIt).i2 + minLength < (*rightIt).i1) {
        while ((*leftIt).i2 + minLength < (*rightIt).i1) {
            if(_isEpsMatch(*leftIt, *rightIt, epsilon)) {
                beginPos = (*leftIt).i2;
                endPos = (*rightIt).i1;
                minLength = endPos - beginPos;
                break;
            }
            --rightIt;
        }
        rightIt = end(gaps) - 1;
        ++leftIt;
    }

    // Set view positions to the eps-match
    TPosition viewBeginRow0 = toSourcePosition(row(align, 0), 0);
    TPosition viewBeginRow1 = toSourcePosition(row(align, 1), 0);
    setClippedEndPosition(row(align, 0), viewBeginRow0 + endPos);
    setClippedEndPosition(row(align, 1), viewBeginRow1 + endPos);
    setClippedBeginPosition(row(align, 0), viewBeginRow0 + beginPos);
    setClippedBeginPosition(row(align, 1), viewBeginRow1 + beginPos);
    // setClippedBeginPosition(row(align, 0), toSourcePosition(row(align, 0), beginPos));
    // setClippedBeginPosition(row(align, 1), toSourcePosition(row(align, 1), beginPos));
    // setBeginPosition(row(align, 0), beginPos);
    // setBeginPosition(row(align, 1), beginPos);
    // setClippedEndPosition(row(align, 0), toSourcePosition(row(align, 0), endPos));
    // setClippedEndPosition(row(align, 1), toSourcePosition(row(align, 1), endPos));
    SEQAN_ASSERT_EQ(length(row(align, 0)), length(row(align, 1)));

    if (endPos == 0 && beginPos == 0) return 1;
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Computes the banded alignment matrix for the left extension and
//   returns a string with possible start positions of an eps-match.
template<typename TMatrix, typename TPossEnd, typename TAlphabet, typename TDiagonal, typename TScore>
void
_fillMatrixBestEndsLeft(TMatrix & matrixLeft,
                        std::vector<TPossEnd> & possibleEndsLeft,
                        //!TODO: should sequencesLeft be owning?
                        std::vector<Segment<std::vector<TAlphabet> const, InfixSegment>> const & sequencesLeft,
                        TDiagonal const diagLower,
                        TDiagonal const diagUpper,
                        TScore const & scoreMatrix) {
    // _align_banded_nw_best_ends(matrixLeft, possibleEndsLeft, str, scoreMatrix,
    //                            upperDiagonal(seedOld) - upperDiagonal(seed),
    //                            upperDiagonal(seedOld) - lowerDiagonal(seed));

    // std::cerr << "FILL MATRIX LEFT SEQS\n"
    //           << "0: " << infixH << "\n"
    //           << "1: " << infixV << "\n";

    // _align_banded_nw_best_ends(matrixLeft, possibleEndsLeft, str, scoreMatrix,
    //                            diagBegin - upperDiagonal(seed),
    //                            diagBegin - lowerDiagonal(seed));
                               // upperDiagonal(seedOld) - upperDiagonal(seed),
                               // upperDiagonal(seedOld) - lowerDiagonal(seed));

    // Use legacy adapted NW computation with infixH/first alignment row being in the vertical direction.
    // // TODO(holtgrew): When switching to DP from new alignment module, make sure to mirror diagonals.
    _align_banded_nw_best_ends(matrixLeft, possibleEndsLeft, sequencesLeft, scoreMatrix, -diagUpper, -diagLower);
}

///////////////////////////////////////////////////////////////////////////////
// Computes the banded alignment matrix for the right extension and
//   returns a string with possible end positions of an eps-match.
template<typename TMatrix, typename TPossEnd, typename TAlphabet, typename TDiagonal, typename TScore>
void
_fillMatrixBestEndsRight(TMatrix & matrixRight,
                         std::vector<TPossEnd> & possibleEndsRight,
                         std::vector<Segment<std::vector<TAlphabet> const, InfixSegment>> const & sequencesRight,
                         TDiagonal const diagLower,
                         TDiagonal const diagUpper,
                         TScore const & scoreMatrix) {
    // std::cerr << "FILL MATRIX RIGHT SEQS\n"
    //           << "0: " << infixH << "\n"
    //           << "1: " << infixV << "\n";

    // _align_banded_nw_best_ends(matrixRight, possibleEndsRight, str, scoreMatrix,
    //                            lowerDiagonal(seedOld) - upperDiagonal(seed),
    //                            lowerDiagonal(seedOld) - lowerDiagonal(seed));

    // _align_banded_nw_best_ends(matrixRight, possibleEndsRight, str, scoreMatrix,
    //                            diagEnd - upperDiagonal(seed),
    //                            diagEnd - lowerDiagonal(seed));
    //                            lowerDiagonal(seedOld) - upperDiagonal(seed),
    //                            lowerDiagonal(seedOld) - lowerDiagonal(seed));

    // Use legacy adapted NW computation with infixH/first alignment row being in the vertical direction.
    // TODO(holtgrew): When switching to DP from new alignment module, make sure to mirror diagonals.
    _align_banded_nw_best_ends(matrixRight, possibleEndsRight, sequencesRight, scoreMatrix, -diagUpper, -diagLower);
}

///////////////////////////////////////////////////////////////////////////////
// Traceback from an arbitrary point (coordinate) in the banded alignment trace matrix (trace).
template <typename TAlign, typename TSegVec, typename TTrace, typename TCoord, typename TDiagonal>
inline void
_alignBandedNeedlemanWunschTrace(TAlign & align,
                                 TSegVec const & str,
                                 TTrace const & trace,
                                 TCoord const & coordinate,
                                 TDiagonal const diagL,
                                 TDiagonal const diagU)
{
    //typedef typename Value<TSegVec>::Type TString;
    typedef typename Id<TSegVec>::Type TId;
    typedef typename Size<TTrace>::Type TSize;
    typedef typename Value<TTrace>::Type TTraceValue;

    // Traceback values
    TTraceValue Diagonal = 0; TTraceValue Horizontal = 1; TTraceValue Vertical = 2;

    // Initialization
    TId id1{0};    // for a owning StringSet<> Id is the same as the index
    TId id2{1};
    TSize lo_row = (diagU <= 0) ? -1 * diagU : 0;
    TSize diagonalWidth = (TSize) (diagU - diagL + 1);

    // Start the trace from the cell with the max value
    TSize row = coordinate.i1;
    TSize col = coordinate.i2;

    // Handle the skipped sequence parts
    TSize actualRow = row + lo_row;
    TSize actualCol = col + diagL + actualRow;

    if ((actualRow != 0) && (actualCol != 0)) {
        // Find initial direction
        TTraceValue tv = trace[row * diagonalWidth + col];
        if (tv == Horizontal) --col;
        else if (tv == Vertical) {--row; ++col;}
        else --row;

        // Walk until we hit a border
        TSize seqLen = 1;
        TTraceValue newTv = tv;
        while(true) {
            actualRow = row + lo_row;
            actualCol = col + diagL + actualRow;
            newTv = trace[row * diagonalWidth + col];

            // Check if we hit a border
            if ((actualRow == 0) || (actualCol == 0)) break;
            else {
                //std::cout << row << ',' << col << ':' << value(originalMat, actualRow * len1 + actualCol) << std::endl;
                if (tv == Diagonal) {
                    if (newTv == Horizontal) {
                        _alignTracePrint(align, str[0], str[1], id1, actualCol, id2, actualRow, seqLen, tv);
                        --col; seqLen = 1;
                    } else if (newTv == Vertical) {
                        _alignTracePrint(align, str[0], str[1], id1, actualCol, id2, actualRow, seqLen, tv);
                        --row; ++col; seqLen = 1;
                    } else {
                        --row; ++seqLen;
                    }
                } else {
                    if (tv == Horizontal) {
                        if (newTv == Diagonal) {
                            _alignTracePrint(align, str[0], str[1], id1, actualCol, id2, actualRow, seqLen, tv);
                            --row; seqLen = 1;
                        } else if (newTv == Vertical) {
                            _alignTracePrint(align, str[0], str[1], id1, actualCol, id2, actualRow, seqLen, tv);
                            --row; ++col; seqLen = 1;
                        } else {
                            --col; ++seqLen;
                        }
                    } else {
                        if (newTv == Diagonal) {
                            _alignTracePrint(align, str[0], str[1], id1, actualCol, id2, actualRow, seqLen, tv);
                            --row; seqLen = 1;
                        } else if (newTv == Horizontal) {
                            _alignTracePrint(align, str[0], str[1], id1, actualCol, id2, actualRow, seqLen, tv);
                            --col; seqLen = 1;
                        } else {
                            --row; ++col; ++seqLen;
                        }
                    }
                }
                tv = newTv;
            }
        }

        // Align left overs
        if (seqLen) _alignTracePrint(align, str[0], str[1], id1, actualCol, id2, actualRow, seqLen, tv);
    }

    // Handle the remaining sequence
    if (actualCol != 0) _alignTracePrint(align, str[0], str[1], (TId) id1, (TSize) 0, (TId) 0, (TSize) 0, (TSize) actualCol,  Horizontal);
    else if (actualRow != 0) _alignTracePrint(align, str[0], str[1], (TId) 0, (TSize) 0, (TId) id2, (TSize) 0, (TSize) actualRow,  Vertical);

}

template <typename TAlign, typename TInfixAlign, typename TPos>
void _copyInfixAlignmentIntoAlignment(TAlign & align,
                                      TInfixAlign const & infixAlign,
                                      TPos const infixAlignHBeginPosition,
                                      TPos const infixAlignVBeginPosition)
{
    using TAlignPos = typename Position<typename Row<TAlign>::Type>::Type;
    String<TAlignPos> viewPos;

    // NOTE: we can't use `integrateAlign(align, infixAlign);` directly
    // as `infixAlign` is a sequence alignment on a local copy of a segment from
    // `align`. That means we need to calculate the positions where to copy
    // the alignment `infixAlign` into `align`.

    TAlignPos pos0 = infixAlignHBeginPosition // beginPosition(infixAlignH) // correct for infixes
                     - beginPosition(source(row(align, 0))) // ...
                     + beginPosition(row(infixAlign, 0)); // respect source clipping

    appendValue(viewPos, toViewPosition(row(align, 0), pos0));

    TAlignPos pos1 = infixAlignVBeginPosition // beginPosition(infixAlignV) // correct for infixes
                     - beginPosition(source(row(align, 1))) // ...
                     + beginPosition(row(infixAlign, 1)); // respect source clipping

    appendValue(viewPos, toViewPosition(row(align, 1), pos1));

    integrateAlign(align, infixAlign, viewPos);
}

///////////////////////////////////////////////////////////////////////////////
// Conducts the traceback on the extension to the left from best start position
//   and writes the result into align.
template<typename TMatrix, typename TCoord, typename TAlphabet, typename TBeginPosition, typename TDiagonal, typename TPos, typename TAlign>
void
_tracebackLeft(TMatrix const & matrixLeft,
               TCoord const & coordinate,
               std::vector<Segment<std::vector<TAlphabet> const, InfixSegment>> const & sequencesLeft,
               TBeginPosition const infixAlignHBeginPosition,
               TBeginPosition const infixAlignVBeginPosition,
               TDiagonal const diagLower,
               TDiagonal const diagUpper,
               TPos const endLeftH,
               TPos const endLeftV,
               TAlign & align) {
    AlignTraceback<TPos> traceBack;
    _alignBandedNeedlemanWunschTrace(traceBack, sequencesLeft, matrixLeft, coordinate,
                                     -diagUpper, -diagLower);
                                     // upperDiagonal(seedOld) - upperDiagonal(seed), upperDiagonal(seedOld) - lowerDiagonal(seed));
  //std::cerr << "TRACEBACK\n";
    //for (unsigned i = 0; i < length(traceBack.tvs); ++i)
  //  std::cerr << (int)traceBack.tvs[i] << "\t" << traceBack.sizes[i] << "\n";
  //std::cerr << "---------\n";

    reverse(traceBack.sizes);
    reverse(traceBack.tvs);

    Align<Segment<std::vector<TAlphabet> const, InfixSegment>> infixAlign;
    resize(rows(infixAlign), 2);
    assignSource(row(infixAlign, 0), infix(sequencesLeft[0], length(sequencesLeft[0]) - endLeftH, length(sequencesLeft[0])));
    assignSource(row(infixAlign, 1), infix(sequencesLeft[1], length(sequencesLeft[1]) - endLeftV, length(sequencesLeft[1])));

    // std::cerr << "\nLEFT SEQS\n" << row(infixAlign, 0) << "\n" << row(infixAlign, 1) << "\n";
    _pumpTraceToGaps(row(infixAlign, 0), row(infixAlign, 1), traceBack);
    // std::cerr << "INFIX ALIGN AFTER LEFT TRACEBACK\n\n" << infixAlign << "\n";
    // std::cerr << "ALIGN BEFORE INTEGRATION WITH INFIX ALIGN\n\n" << align << "\n";
    _copyInfixAlignmentIntoAlignment(align, infixAlign, infixAlignHBeginPosition, infixAlignVBeginPosition);
    // std::cerr << "ALIGN AFTER INTEGRATION WITH INFIX ALIGN\n\n" << align << "\n";
}


///////////////////////////////////////////////////////////////////////////////
// Conducts the traceback on the extension to the right from best end position
//   and writes the result into align.
template<typename TMatrix, typename TCoord, typename TAlphabet, typename TBeginPosition, typename TDiagonal, typename TPos, typename TAlign>
void
_tracebackRight(TMatrix const & matrixRight,
               TCoord const & coordinate,
               std::vector<Segment<std::vector<TAlphabet> const, InfixSegment>> const & sequencesRight,
               TBeginPosition const infixAlignHBeginPosition,
               TBeginPosition const infixAlignVBeginPosition,
               TDiagonal const diagLower,
               TDiagonal const diagUpper,
               TPos const endRightH,
               TPos const endRightV,
               TAlign & align) {
    AlignTraceback<TPos> traceBack;
    _alignBandedNeedlemanWunschTrace(traceBack, sequencesRight, matrixRight, coordinate,
                                     -diagUpper, -diagLower);
                // lowerDiagonal(seedOld) - upperDiagonal(seed), lowerDiagonal(seedOld) - lowerDiagonal(seed));
  //std::cerr << "TRACEBACK\n";
    //for (unsigned i = 0; i < length(traceBack.tvs); ++i)
  //  std::cerr << (int)traceBack.tvs[i] << "\t" << traceBack.sizes[i] << "\n";
  //std::cerr << "---------\n";

    Align<Segment<std::vector<TAlphabet> const, InfixSegment>> infixAlign;
    resize(rows(infixAlign), 2);
    assignSource(row(infixAlign, 0), infix(sequencesRight[0], 0, endRightH));
    assignSource(row(infixAlign, 1), infix(sequencesRight[1], 0, endRightV));

    // std::cerr << "\nRIGHT SEQS\n" << row(infixAlign, 0) << "\n" << row(infixAlign, 1) << "\n";
    _pumpTraceToGaps(row(infixAlign, 0), row(infixAlign, 1), traceBack);
    // std::cerr << "INFIX ALIGN AFTER RIGHT TRACEBACK\n\n" << infixAlign << "\n";
    // std::cerr << "ALIGN BEFORE INTEGRATION WITH INFIX ALIGN\n\n" << align << "\n";
    _copyInfixAlignmentIntoAlignment(align, infixAlign, infixAlignHBeginPosition, infixAlignVBeginPosition);
    // std::cerr << "ALIGN AFTER INTEGRATION WITH INFIX ALIGN\n\n" << align << "\n";
}

///////////////////////////////////////////////////////////////////////////////
// Computes the banded alignment matrix and fills a string with possible start
//   and end positions of an eps-match. Determines the optimal start and end
//   position for the longest eps-match and writes the trace into align.
template<typename TSequence, typename TSeed, typename TPos, typename TDir, typename TScore,
         typename TSize, typename TEps, typename TAlign>
bool
_bestExtension(Segment<TSequence const, InfixSegment> const & infH, // database
               Segment<TSequence const, InfixSegment> const & infV, // query
               TSeed const & seed,
               TSeed const & seedOld,
               TPos const alignLen,
               TPos const alignErr,
               TScore const & scoreMatrix,
               TDir const direction,
               TSize const minLength,
               TEps const eps,
               TAlign & align,
               stellar_best_extension_time & best_extension_runtime)
{
    using TAlphabet = std::remove_cv<typename TSequence::value_type>::type;
    using TOwningContainer = std::vector<TAlphabet>;

    typedef std::vector<TraceBack>                                TAlignmentMatrix;
    typedef ExtensionEndPosition<TPos>                            TEndInfo;
    typedef typename std::vector<TEndInfo>::const_iterator        TEndIterator;
    typedef typename Diagonal<TSeed>::Type                        TDiagonal;

    // variables for banded alignment and possible ends of match
    TAlignmentMatrix matrixRight, matrixLeft;
    std::vector<TEndInfo> possibleEndsLeft, possibleEndsRight;

    // new extension to the left of the old seed
    assert(beginPositionH(seed) <= beginPositionH(seedOld)); // infixLeftH
    assert(beginPositionV(seed) <= beginPositionV(seedOld)); // infixLeftV

    // old seed covers at least one character
    assert(beginPositionH(seedOld) < endPositionH(seedOld));
    assert(beginPositionV(seedOld) < endPositionV(seedOld));

    // new extension to the right of the old seed
    assert(endPositionH(seedOld) <= endPositionH(seed)); // infixRightH
    assert(endPositionV(seedOld) <= endPositionV(seed)); // infixRightV

    std::vector<Segment<TOwningContainer const, InfixSegment>> sequencesLeft;
    std::vector<Segment<TOwningContainer const, InfixSegment>> sequencesRight;

    // Compute diagonals for updated seeds module with infixH/first alignment row being in the horizontal direction.
    TDiagonal const diagLowerLeft = lowerDiagonal(seedOld) - upperDiagonal(seed);
    TDiagonal const diagUpperLeft = lowerDiagonal(seedOld) - lowerDiagonal(seed);

    // Compute diagonals for updated seeds module with infixH/first alignment row being in the horizontal direction.
    TDiagonal const diagLowerRight = upperDiagonal(seedOld) - upperDiagonal(seed);
    TDiagonal const diagUpperRight = upperDiagonal(seedOld) - lowerDiagonal(seed);

    best_extension_runtime.banded_needleman_wunsch_time.measure_time([&]()
    {
    // fill banded matrix and gaps string for ...
    if (direction == EXTEND_BOTH || direction == EXTEND_LEFT) { // ... extension to the left
        // prepare copy segment...
        //!TODO: can these be references instead of copies?
        TOwningContainer segmentCopyLeftH;
        TOwningContainer segmentCopyLeftV;
        segmentCopyLeftH.reserve(beginPositionH(seedOld) - beginPositionH(seed));
        segmentCopyLeftV.reserve(beginPositionV(seedOld) - beginPositionV(seed));

        best_extension_runtime.banded_needleman_wunsch_left_time.measure_time([&]()
        {
        // ...copy reverse complement segment
        //!TODO: are seqan2 and seqan3 ranks compatible?
        for (auto n : host(infH).subspan(beginPositionH(seed), beginPositionH(seedOld)) | std::views::reverse | seqan3::views::complement)
        {
            segmentCopyLeftH.emplace_back(n.to_rank());
        }

        for (auto n : host(infV).subspan(beginPositionV(seed), beginPositionV(seedOld)) | std::views::reverse | seqan3::views::complement)
        {
            segmentCopyLeftV.emplace_back(n.to_rank());
        }

        // put infix segments
        sequencesLeft.emplace_back(infix(segmentCopyLeftH, 0, segmentCopyLeftH.size()));
        sequencesLeft.emplace_back(infix(segmentCopyLeftV, 0, segmentCopyLeftV.size()));

        _fillMatrixBestEndsLeft(matrixLeft, possibleEndsLeft, sequencesLeft, diagLowerLeft, diagUpperLeft, scoreMatrix);
        SEQAN_ASSERT_NOT(possibleEndsLeft.empty());
        }); // measure_time
    } 
    else 
        possibleEndsLeft.emplace_back(TEndInfo());
    if (direction == EXTEND_BOTH || direction == EXTEND_RIGHT) { // ... extension to the right
        best_extension_runtime.banded_needleman_wunsch_right_time.measure_time([&]()
        {
        // prepare copy segment...
        //!TODO: can these be references instead of copies?
        auto segmentCopyRightH = TOwningContainer(host(infH).begin() + endPositionH(seedOld), host(infH).begin() + endPositionH(seed));
        auto segmentCopyRightV = TOwningContainer(host(infV).begin() + endPositionV(seedOld), host(infV).begin() + endPositionV(seed));

        sequencesRight.emplace_back(infix(segmentCopyRightH, 0, segmentCopyRightH.size()));
        sequencesRight.emplace_back(infix(segmentCopyRightV, 0, segmentCopyRightV.size()));
        _fillMatrixBestEndsRight(matrixRight, possibleEndsRight, sequencesRight, diagLowerRight, diagUpperRight, scoreMatrix);
        SEQAN_ASSERT_NOT(possibleEndsRight.empty());
        }); // measure_time
    } else
    {
        possibleEndsRight.emplace_back(TEndInfo());
    } 
    }); // measure_time

    // longest eps match on poss ends string
    std::pair<TEndIterator, TEndIterator> endPair = best_extension_runtime.longest_eps_match_time.measure_time([&]()
    {
        return longestEpsMatch(possibleEndsLeft, possibleEndsRight, alignLen, alignErr, minLength, eps);
    });

    if (endPair == std::pair<TEndIterator, TEndIterator>(possibleEndsLeft.end(), possibleEndsRight.end())) { // no eps-match found
        return false;
    }

    // determine end positions of maximal eps-match in ...
    TPos endLeftH = 0, endLeftV = 0;
    TPos endRightH = 0, endRightV = 0;
    if((*endPair.first).length != 0) { // ... extension to the left
        endLeftV = (*endPair.first).coord.i1;
        // correction for banded coordinates to unbanded:
        if (diagLowerLeft >= 0)
            endLeftV += (TPos)(diagLowerLeft);
        endLeftH = endLeftV + (TPos)((*endPair.first).coord.i2 - diagUpperLeft);
    }
    if((*endPair.second).length != 0) { // ... extension to the right
        endRightV = (*endPair.second).coord.i1;
        // correction for banded coordinates to unbanded:
        if (diagLowerRight >= 0)
            endRightV += (TPos)(diagLowerRight);
        endRightH = endRightV + (TPos)((*endPair.second).coord.i2 - diagUpperRight);
    }

    // set begin and end positions of align
    setBeginPosition(row(align, 0), beginPositionH(seedOld) - endLeftH);
    setBeginPosition(row(align, 1), beginPositionV(seedOld) - endLeftV);
    setEndPosition(row(align, 0), endPositionH(seedOld) + endRightH);
    setEndPosition(row(align, 1), endPositionV(seedOld) + endRightV);
    // setClippedBeginPosition(row(align, 0), beginPositionH(seedOld) - endLeftH);
    // setClippedBeginPosition(row(align, 1), beginPositionV(seedOld) - endLeftV);
    // setBeginPosition(row(align, 0), 0);
    // setBeginPosition(row(align, 1), 0);
    // setClippedEndPosition(row(align, 0), endPositionH(seedOld) + endRightH);
    // setClippedEndPosition(row(align, 1), endPositionV(seedOld) + endRightV);

    best_extension_runtime.construct_seed_alignment_time.measure_time([&]()
    {
    // traceback through matrix from begin/end pos on ...
    if((*endPair.first).length != 0) { // ... extension to the left
        assert(direction == EXTEND_BOTH || direction == EXTEND_LEFT);
        auto const infixAlignHBeginPosition = beginPositionH(seed) + length(sequencesLeft[0]) - endLeftH;
        auto const infixAlignVBeginPosition = beginPositionV(seed) + length(sequencesLeft[1]) - endLeftV;
        _tracebackLeft(matrixLeft,
                       (*endPair.first).coord,
                       sequencesLeft,
                       infixAlignHBeginPosition,
                       infixAlignVBeginPosition,
                       diagLowerLeft,
                       diagUpperLeft,
                       endLeftH,
                       endLeftV,
                       align);
    }
    if((*endPair.second).length != 0) { // ... extension to the right
        assert(direction == EXTEND_BOTH || direction == EXTEND_RIGHT);
        auto const infixAlignHBeginPosition = endPositionH(seedOld);
        auto const infixAlignVBeginPosition = endPositionV(seedOld);
        _tracebackRight(matrixRight,
                        (*endPair.second).coord,
                        sequencesRight,
                        infixAlignHBeginPosition,
                        infixAlignVBeginPosition,
                        diagLowerRight,
                        diagUpperRight,
                        endRightH,
                        endRightV,
                        align);
    }
    SEQAN_ASSERT_EQ(length(row(align, 0)), length(row(align, 1)));
    }); // measure_time

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename TSource, typename TSpec1, typename TSpec2>
void
integrateAlign(Align<TSource, TSpec1> & align,
               Align<Segment<Segment<TSource const, InfixSegment>, InfixSegment>, TSpec2> const & infixAlign) {
    typedef typename Size<TSource const>::Type TSize;
    typedef typename Position<typename Row<Align<TSource const, TSpec1> >::Type>::Type TPos;

    String<TPos> viewPos;
    TPos pos;
    for (TSize i = 0; i < length(rows(infixAlign)); ++i) {
        pos = beginPosition(source(row(infixAlign, i))) + beginPosition(row(infixAlign, i));
        pos += beginPosition(host(source(row(infixAlign, i))));
        appendValue(viewPos, toViewPosition(row(align, i), pos));
    }

    // std::cerr << "HAHA infixAlign == \n" << row(infixAlign, 0) << "\n" << row(infixAlign, 1) << "\n";
    integrateAlign(align, infixAlign, viewPos);
    // std::cerr << "HAHA infixAlign == \n" << row(infixAlign, 0) << "\n" << row(infixAlign, 1) << "\n";
}

///////////////////////////////////////////////////////////////////////////////
// Conducts best X-drop extension and calls _bestExtension.
//  After the call align contains the longest eps-Match that spans the eps-core (localAlign).
template<typename TScoreValue, typename TScore, typename TSequence, typename TSize, typename TEps, typename TAlign>
bool
_extendAndExtract(Align<Segment<Segment<TSequence const, InfixSegment>, InfixSegment> > const & localAlign,
                  TScoreValue const scoreDropOff,
                  TScore const & scoreMatrix,
                  Segment<Segment<TSequence const, InfixSegment>, InfixSegment> const & infH,
                  Segment<Segment<TSequence const, InfixSegment>, InfixSegment> const & infV,
                  ExtensionDirection const direction,
                  TSize const minLength,
                  TEps const eps,
                  TAlign & align,
                  stellar_extension_time & extension_runtime) {
    typedef typename Position<TSequence>::Type TPos;
    typedef Seed<Simple> TSeed;

    //!NOTE: TSequence = std::span<TAlphabet>

    // std::cerr << "LOCAL ALIGN\n" << row(localAlign, 0) << "\n" << row(localAlign, 1) << "\n";
    // std::cerr << "ALIGN\n" << row(align, 0) << "\n" << row(align, 1) << "\n";
    integrateAlign(align, localAlign);
    //std::cerr << __LINE__ << "\tLOCAL ALIGN\n" << row(localAlign, 0) << "\n" << row(localAlign, 1) << "\n";
    //std::cerr << __LINE__ << "\tALIGN\n" << row(align, 0) << "\n" << row(align, 1) << "\n";

    // Get begin and end position of local alignment (seed) as source positions
    // in underlying sequences.
    TPos seedBeginH = beginPosition(row(localAlign, 0)) + beginPosition(infH);
    TPos seedBeginV = beginPosition(row(localAlign, 1)) + beginPosition(infV);
    TPos seedEndH = endPosition(row(localAlign, 0)) + beginPosition(infH);
    TPos seedEndV = endPosition(row(localAlign, 1)) + beginPosition(infV);

    if (direction == EXTEND_NONE) {
        // set begin and end positions of align
        setBeginPosition(row(align, 0), seedBeginH);
        setBeginPosition(row(align, 1), seedBeginV);
        setEndPosition(row(align, 0), seedEndH);
        setEndPosition(row(align, 1), seedEndV);

        if ((TSize)length(row(align, 0)) < minLength)
            return false;

        longestEpsMatch(align, minLength, eps);
    } else {
        // gapped X-drop extension of local alignment (seed)
        TSeed seed(seedBeginH, seedBeginV, seedEndH, seedEndV);
        TSeed seedOld(seed);

        static_assert(std::is_same<decltype(host(infH)), Segment<TSequence const, InfixSegment>>::value,
                      "infH is a nested InfixSegment: Segment<Segment<TSequence const, InfixSegment>, InfixSegment>");
        Segment<TSequence const, InfixSegment> infixSequenceH = host(infH); // inner nested Segment
        Segment<TSequence const, InfixSegment> infixSequenceV = host(infV); // inner nested Segment
        extension_runtime.extend_seed_time.measure_time([&]()
        {
            extendSeed(seed, infixSequenceH, infixSequenceV, direction, scoreMatrix, scoreDropOff, GappedXDrop());
        });
        if (static_cast<int64_t>(seedSize(seed)) < minLength - (int)floor(minLength*eps))
            return false;

        // determine length and number of error columns of local alignment (seed)
        TPos alignLen = _max(length(row(localAlign, 0)), length(row(localAlign, 1)));
        TPos alignErr = 0;
        for (TPos i = 0; i < alignLen; ++i) {
            if (!isMatch(localAlign, i)) ++alignErr;
        }

        // convert seeds from positions in host(seq) to positions in host(host(seq))
        setBeginPositionH(seedOld, beginPositionH(seedOld) + beginPosition(host(infH)));
        setEndPositionH(seedOld, endPositionH(seedOld) + beginPosition(host(infH)));
        setBeginPositionV(seedOld, beginPositionV(seedOld) + beginPosition(host(infV)));
        setEndPositionV(seedOld, endPositionV(seedOld) + beginPosition(host(infV)));
        setBeginPositionH(seed, beginPositionH(seed) + beginPosition(host(infH)));
        setEndPositionH(seed, endPositionH(seed) + beginPosition(host(infH)));
        setBeginPositionV(seed, beginPositionV(seed) + beginPosition(host(infV)));
        setEndPositionV(seed, endPositionV(seed) + beginPosition(host(infV)));

        // determine best extension lengths and write the trace into align
        Segment<TSequence const, InfixSegment> infixH = infix(infixSequenceH, beginPosition(infH), endPosition(infH));
        Segment<TSequence const, InfixSegment> infixV = infix(infixSequenceV, beginPosition(infV), endPosition(infV));

        bool const found_extension = extension_runtime.best_extension_time.measure_time([&]()
        {
            return _bestExtension(infixH, infixV, seed, seedOld, alignLen, alignErr, scoreMatrix, direction, minLength, eps, align, extension_runtime.best_extension_time);
        });
        if (!found_extension)
            return false;
        SEQAN_ASSERT_EQ(length(row(align, 0)), length(row(align, 1)));
    }
    SEQAN_ASSERT_EQ(length(row(align, 0)), length(row(align, 1)));
    //std::cerr << "extracted alignment\n-------------\n" << align << "----------------\n";
    return true;
}

} // namespace dream_stellar
