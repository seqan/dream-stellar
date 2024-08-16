#pragma once

#include <iostream>
#include <seqan/seeds.h>

#include <dream_stellar/stellar_types.hpp>
#include <dream_stellar/stellar_extension.hpp>
#include <dream_stellar/stellar_database_segment.hpp>
#include <dream_stellar/stellar_query_segment.tpp>
#include <dream_stellar/stellar_index.hpp>
#include <dream_stellar/utils/stellar_kernel_runtime.hpp>
#include <dream_stellar/verification/all_local.hpp>
#include <dream_stellar/verification/banded_global_extend.hpp>
#include <dream_stellar/verification/banded_global.hpp>
#include <dream_stellar/verification/best_local.hpp>
#include <dream_stellar/verification/swift_hit_verifier.hpp>

#include <utilities/alphabet_wrapper/matcher/stellar_matcher.hpp>

#include <dream_stellar/diagnostics/print.hpp>

namespace dream_stellar
{

using namespace seqan2;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Checks whether two matches overlap *in seq2* and
//  whether the non-overlaping parts are shorter than minLength.
template<typename TMatch, typename TSize>
bool
checkOverlap(TMatch const & matchA, TMatch const & matchB, TSize const minLength) {
    // check id and orienation
    if (matchA.id != matchB.id || matchA.orientation != matchB.orientation) return false;
    if (matchA.id == TMatch::INVALID_ID || matchB.id == TMatch::INVALID_ID) return false;

    // check overlap in seq2
    if (matchA.begin2 >= matchB.begin2) {
        if (matchA.end2 >= matchB.end2) {
            // check length of non-overlapping parts of both matches
            if ((TSize)matchA.begin2 - (TSize)matchB.begin2 >= minLength &&
                (TSize)matchA.end2 - (TSize)matchB.end2 >= minLength) {
                return false;
            }
        }
        // check whether offset is the same in both sequences
        if (toViewPosition(matchA.row2, matchA.begin2) - toViewPosition(matchB.row2, matchB.begin2) !=
            toViewPosition(matchA.row1, matchA.begin1) - toViewPosition(matchB.row1, matchB.begin1)) {
            return false;
        }
    } else {
        if (matchA.end2 < matchB.end2) {
            // check length of non-overlapping parts of both matches
            if ((TSize)matchB.begin2 - (TSize)matchA.begin2 >= minLength &&
                (TSize)matchB.end2 - (TSize)matchA.end2 >= minLength) {
                return false;
            }
        }
        // check whether offset is the same in both sequences
        if (toViewPosition(matchB.row2, matchB.begin2) - toViewPosition(matchA.row2, matchA.begin2) !=
            toViewPosition(matchB.row1, matchB.begin1) - toViewPosition(matchA.row1, matchA.begin1)) {
            return false;
        }
    }
    return true;
}

template<typename TRow, typename TPosition>
TPosition
projectedPosition(TRow const & rowA, TRow const & rowB, TPosition pos)
{
    return toSourcePosition(rowB, toViewPosition(rowA, pos));
}

///////////////////////////////////////////////////////////////////////////////
// Checks all alignment columns of two overlapping matches.
// It is assumed that matchA.begin1 < matchB.begin1.
template<typename TMatch, typename TSize>
bool
_checkAlignColOverlap(TMatch const & matchA, TMatch const & matchB, TSize const minLength)
{
    TSize equalCols = 0;
    TSize diffCols = 0;

    for  (typename TMatch::TPos pos = matchB.begin1; pos < _min(matchA.end1, matchB.end1); ++pos)
    {
        if (projectedPosition(matchA.row1, matchA.row2, pos) == projectedPosition(matchB.row1, matchB.row2, pos))
            ++equalCols;
        else
            ++diffCols;
    }

    if (diffCols >= minLength) return false;
    return true;
}

///////////////////////////////////////////////////////////////////////////////
// Marks matches that overlap in both sequences with a longer match as invalid.
template<typename TSequence, typename TId, typename TSize>
void maskOverlaps(String<StellarMatch<TSequence const, TId> > & matches, TSize const minLength)
{
    typedef StellarMatch<TSequence const, TId>              TMatch;
    typedef typename TMatch::TPos                           TPos;
    typedef typename Iterator<String<TMatch>, Rooted>::Type TIter;
    typedef typename Iterator<String<TSize>, Rooted>::Type  TOverlapIter;

    // sort matches by begin position in row0
    sortMatches(matches, LessPos<TMatch>());

    // iterate all matches
    TIter it = begin(matches);

    // list of matches that potentially overlap with the current match in row0 and
    // start earlier (including matches that overlap but have a unique part of at
    // least minLength) sorted by descending end positions
    String<TSize> overlaps;

    for (; it != end(matches); ++it)
    {
        if ((*it).id == TMatch::INVALID_ID) continue;

        TPos insertPos = 0;

        // iterate potentially overlapping matches
        TOverlapIter overlapIt = begin(overlaps);
        for (; overlapIt != end(overlaps); ++overlapIt)
        {
            TMatch & o = matches[*overlapIt];

            // determine position for inserting *it into overlaps after checking
            if ((*it).end1 < o.end1) insertPos++;

            // check if matches overlap in row0 - if not, then break
            if (o.end1 <= (*it).begin1) break;

            // check if unique parts of the two matches in row0 are longer than minLength - if yes, then continue
            if ((*it).begin1 - o.begin1 >= (TPos)minLength &&
                (*it).end1 > o.end1 && (*it).end1 - o.end1 >= (TPos)minLength) continue;

            // check if matches overlap in row1 - if not, then continue
            if (!checkOverlap(*it, o, minLength)) continue;

            // check exact alignment columns for overlap
            if (!_checkAlignColOverlap(o, *it, minLength)) continue;

            // set shorter match invalid
            if (length(*it) > length(o))
                o.id = TMatch::INVALID_ID;
            else
                (*it).id = TMatch::INVALID_ID;
        }

        // remove all matches from overlaps that end earlier than current match begins
        resize(overlaps, position(overlapIt));

        if ((*it).id != TMatch::INVALID_ID)
            insertValue(overlaps, insertPos, position(it));
    }

}

///////////////////////////////////////////////////////////////////////////////
// Removes matches that are marked as invalid, and then keeps only the numMatches best matches.
template<typename TSequence, typename TId, typename TSize>
void
compactMatches(String<StellarMatch<TSequence const, TId> > & matches, TSize const numMatches) {
    typedef StellarMatch<TSequence const, TId>                  TMatch;
    typedef typename Iterator<String<TMatch>, Standard>::Type   TIterator;

    // sort matches by length (and validity)
    sortMatches(matches, LessLength<TMatch>());

    // count valid matches
    TSize num = 0;

    TIterator it = begin(matches, Standard());
    TIterator itEnd = end(matches, Standard());

    for(; it != itEnd; ++it) {
        if ((*it).id != TMatch::INVALID_ID)
            ++num;
    }

    // keep only valid and longest matches
    resize(matches, _min(num, numMatches));
}

///////////////////////////////////////////////////////////////////////////////
// Calls swift filter and verifies swift hits. = Computes eps-matches.
// A basic block for stellar
template<typename alphabet_t, typename TTag, typename TIsPatternDisabledFn, typename TOnAlignmentResultFn>
StellarComputeStatistics
_stellarKernel(jst::contrib::stellar_matcher<std::span<alphabet_t>> & matcher,
               StellarDatabaseSegment<alphabet_t> & database_segment,
               StellarOptions & localOptions,
               SwiftHitVerifier<TTag> & swiftVerifier,
               TIsPatternDisabledFn && isPatternDisabled,
               TOnAlignmentResultFn && onAlignmentResult,
               stellar_kernel_runtime & stellar_kernel_runtime) 
{
    StellarComputeStatistics statistics{};

    auto finder_callback = [&](auto & finder)
    {
        bool has_next = stellar_kernel_runtime.swift_filter_time.measure_time([&]()
        {
            return jst::contrib::find(finder, matcher/*!TODO: , swiftVerifier.eps_match_options.epsilon, swiftVerifier.eps_match_options.minLength*/);
        });

        if (has_next)
            seqan3::debug_stream << "FOUND MATCH\n";

        StellarDatabaseSegment<alphabet_t> databaseSegment
        = StellarDatabaseSegment<alphabet_t>::fromFinderMatch(infix(finder));

        ++statistics.numSwiftHits;
        statistics.totalLength += databaseSegment.size();
        statistics.maxLength = std::max<size_t>(statistics.maxLength, databaseSegment.size());

        if (!isPatternDisabled(matcher))
        {
            //!TODO: adjust for alphabet_t
            /*  
            StellarQuerySegment<alphabet_t> querySegment
                = StellarQuerySegment<TAlphabet>::fromPatternMatch(pattern);

            ////Debug stuff:
            //std::cout << beginPosition(infix(finder)) << ",";
            //std::cout << endPosition(infix(finder)) << "  ";
            //std::cout << beginPosition(pattern) << ",";
            //std::cout << endPosition(pattern) << std::endl;

            // verification
            stellar_kernel_runtime.verification_time.measure_time([&]()
            {
                swiftVerifier.verify(
                    databaseSegment,
                    querySegment,
                    pattern.bucketParams[0].delta + pattern.bucketParams[0].overlap,
                    onAlignmentResult,
                    stellar_kernel_runtime.verification_time);
            }); // measure_time
        */
        }
    };

    // call operator() from seqan_pattern_base
    matcher(database_segment, localOptions.minRepeatLength, localOptions.maxRepeatPeriod, finder_callback);

    return statistics;
}

} // namespace dream_stellar
