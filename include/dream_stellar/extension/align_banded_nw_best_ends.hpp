
#pragma once

#include <seqan/seeds.h>

namespace dream_stellar
{
using namespace seqan2;

///////////////////////////////////////////////////////////////////////////////
// Computes the banded alignment matrix and additionally a string with the best
//   alignment end point for each alignment length.
template <typename TTrace, typename TEnd, typename TStringSet, typename TScore, typename TDiagonal>
inline void
_align_banded_nw_best_ends(TTrace& trace,
                           String<TEnd> & bestEnds,
                           TStringSet const & str,
                           TScore const & sc,
                           TDiagonal const diagL,
                           TDiagonal const diagU)
{
    typedef typename Value<TTrace>::Type TTraceValue;
    typedef typename Value<TScore>::Type TScoreValue;
    typedef typename Value<TStringSet>::Type TString;
    typedef typename Size<TTrace>::Type TSize;
    using TAlphabet = typename Value<TString>::Type;

    SEQAN_ASSERT_GEQ(diagU, diagL);

    // Initialization
    TTraceValue const Diagonal = 0;
    TTraceValue const Horizontal = 1;
    TTraceValue const Vertical = 2;
    TString const& str1 = str[0];
    TString const& str2 = str[1];
    TSize const len1 = length(str1) + 1;
    TSize const len2 = length(str2) + 1;
    TSize const diagonalWidth = (TSize) (diagU - diagL + 1);
    TSize hi_diag = diagonalWidth;
    TSize lo_diag = 0;
    if (diagL > 0) lo_diag = 0;
    else lo_diag = (diagU < 0) ? hi_diag : (TSize) (1 - diagL);
    TSize const lo_row = (diagU <= 0) ? -diagU : 0;
    TSize const hi_row = [&]()
    {
        TSize const max_hi_row = len2;
        // Note: diagL might be negative
        assert((TDiagonal) len1 >= diagL);
        if (len1 - diagL < max_hi_row)
            return len1 - diagL;
        else
            return max_hi_row;
    }();
    TSize const height = hi_row - lo_row;

    typedef String<TScoreValue> TRow;
    TRow mat, len;
    resize(mat, diagonalWidth);
    resize(len, diagonalWidth);
    resize(trace, height * diagonalWidth);

    // Classical DP with affine gap costs
    typedef typename Iterator<TRow, Standard>::Type TRowIter;
    typedef typename Iterator<TTrace, Standard>::Type TTraceIter;

    TSize errors;

    assert(scoreMatch(sc) == 1u);
    assert(scoreGap(sc) == scoreGapExtendHorizontal(sc, TAlphabet{}, TAlphabet{}));
    assert(scoreGap(sc) == scoreGapExtendVertical(sc, TAlphabet{}, TAlphabet{}));
    assert(scoreMismatch(sc) == scoreGap(sc));

    TScoreValue const matchScore = scoreMatch(sc);
    TScoreValue const gapScore = scoreGap(sc);

    for(TSize row = 0; row < height; ++row) {
        TSize actualRow = row + lo_row;
        if (lo_diag > 0) --lo_diag;
        if ((TDiagonal)actualRow >= (TDiagonal)len1 - diagU) --hi_diag;
        TTraceIter traceIt = begin(trace, Standard()) + row * diagonalWidth + lo_diag;
        TRowIter current_score_rowise_it = begin(mat, Standard()) + lo_diag;
        TRowIter alignment_length_it = begin(len, Standard()) + lo_diag;

        TScoreValue score_left = std::numeric_limits<TScoreValue>::min();
        TScoreValue alignment_length_left = len1+len2+1;

        for(TSize col = lo_diag; col<hi_diag; ++col, ++current_score_rowise_it, ++traceIt, ++alignment_length_it) {
            TSize actualCol = col + diagL + actualRow;
            if (actualCol >= len1) break;

            if ((actualRow != 0) && (actualCol != 0)) {
                TAlphabet const str1entry = sequenceEntryForScore(sc, str1, ((int) actualCol - 1));
                TAlphabet const str2entry = sequenceEntryForScore(sc, str2, ((int) actualRow - 1));

                // Get the new maximum for mat
                *current_score_rowise_it += score(sc, str1entry, str2entry);
                *traceIt = Diagonal;
                ++(*alignment_length_it);

                TScoreValue score_up =
                    (col < diagonalWidth - 1) ?
                    *(current_score_rowise_it+1) + gapScore :
                    std::numeric_limits<TScoreValue>::min();

                if (score_up > *current_score_rowise_it)
                {
                    *current_score_rowise_it = score_up;
                    *traceIt = Vertical;
                    *alignment_length_it = *(alignment_length_it+1) + 1;
                }

                score_left =
                    (col > 0) ?
                    score_left + gapScore :
                    std::numeric_limits<TScoreValue>::min();
                if (score_left > *current_score_rowise_it)
                {
                    *current_score_rowise_it = score_left;
                    *traceIt = Horizontal;
                    *alignment_length_it = alignment_length_left + 1;
                }
                score_left = *current_score_rowise_it;
                alignment_length_left = *alignment_length_it;
            } else {
                // Usual initialization for first row and column
                if (actualRow == 0) {
                    *current_score_rowise_it = actualCol * gapScore;
                    *alignment_length_it = actualCol;
                }
                else {
                    assert(actualCol == 0);
                    *current_score_rowise_it = actualRow * gapScore;
                    *alignment_length_it = actualRow;
                    score_left = *current_score_rowise_it;
                    alignment_length_left = actualRow;
                }
            }

            // *current_score_rowise_it: the alignment_score
            // *alignment_length_it: the alignment_length (basically length of best trace path of the current cell)
            // alignment_length = |matches| + |mismatches| + |gaps|
            //
            // alignment_score
            //     = |matches| * match_score + |mismatches| * gap_score + |gaps| * gap_score
            //
            // alignment_length * match_score
            //     = |matches| * match_score + |mismatches| * match_score + |gaps| * match_score
            //
            // alignment_score - alignment_length * match_score
            //     = 0 + (|mismatches| + |gaps|)(gap_score - match_score)
            //
            // Thus
            //   (alignment_score - alignment_length * match_score) / (gapScore - matchScore)
            // = |mismatches| + |gaps| = errors
            errors = (*current_score_rowise_it - (*alignment_length_it * matchScore)) / (gapScore - matchScore);
            SEQAN_ASSERT_GEQ(errors, 0);
            SEQAN_ASSERT_LEQ(errors, length(bestEnds));
            if (errors == length(bestEnds)) {
                appendValue(bestEnds, TEnd(*alignment_length_it, row, col));
            } else if (*alignment_length_it > static_cast<TScoreValue>(value(bestEnds, errors).length))
                value(bestEnds, errors) = TEnd(*alignment_length_it, row, col);
            //std::cerr << row << ',' << col << ':' << *current_score_rowise_it << std::endl;
        }
    }
    TSize newLength = length(bestEnds) - 1;
    while (newLength > 0 && bestEnds[newLength].length <= bestEnds[newLength-1].length) {
        --newLength;
    }
    resize(bestEnds, newLength + 1);
}

} // namespace dream_stellar
