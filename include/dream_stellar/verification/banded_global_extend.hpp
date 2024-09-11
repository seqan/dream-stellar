
#pragma once

#include <dream_stellar/stellar_extension.hpp>
#include <dream_stellar/stellar_types.hpp>
#include <dream_stellar/utils/stellar_kernel_runtime.hpp>

namespace dream_stellar
{

///////////////////////////////////////////////////////////////////////////////
// Conducts banded alignment on swift hit, extends alignment, and extracts longest contained eps-match.
template<typename TSequence, typename TEpsilon, typename TSize, typename TDrop, typename TDelta,
         typename TOnAlignmentResultFn>
void
verifySwiftHit(Segment<Segment<TSequence const, InfixSegment>, InfixSegment> const & infH,
               Segment<Segment<TSequence const, InfixSegment>, InfixSegment> const & infV,
               TEpsilon const eps,
               TSize const minLength,
               TDrop const xDrop,
               TDelta const delta,
               TOnAlignmentResultFn && onAlignmentResult,
               stellar_verification_time & verification_runtime,
               BandedGlobalExtend) {
    using TInfix = Segment<TSequence const, InfixSegment>;
    typedef Segment<TInfix, InfixSegment> TSegment;
    typedef typename StellarMatch<TSequence const, CharString>::TAlign TAlign;

    // define a scoring scheme
    typedef int TScore;
    TScore match = 1;
    // large negative scoring scheme values lead to excessive seed extension 
    TScore scoringSchemeLowerBound = -(TScore)1000;
    TScore mismatchIndel = scoringSchemeLowerBound;
    if (eps > -1/scoringSchemeLowerBound)   // avoid division by 0
        mismatchIndel = (TScore)_max((TScore) std::ceil(-1/eps) + 1, -(TScore)length(host(infH)));
    Score<TScore> scoreMatrix(match, mismatchIndel, mismatchIndel);
    TScore scoreDropOff = (TScore) _max((TScore) xDrop * (-mismatchIndel), MinValue<TScore>::VALUE + 1);

    // diagonals for banded alignment
    int64_t upperDiag = 0;
    int64_t lowerDiag = endPosition(infH) - (int64_t)endPosition(infV) - beginPosition(infH) + beginPosition(infV);
    if (beginPosition(infV) == 0) upperDiag = lowerDiag + delta;
    if (endPosition(infV) == endPosition(host(infV))) lowerDiag = -(int64_t)delta;

    // banded alignment on parallelogram
    Align<TSegment> bandedAlign;
    resize(rows(bandedAlign), 2);
    assignSource(row(bandedAlign, 0), infH);
    assignSource(row(bandedAlign, 1), infV);
    globalAlignment(bandedAlign, scoreMatrix, lowerDiag, upperDiag, NeedlemanWunsch());

    // create alignment object for the complete sequences
    TAlign align;
    resize(rows(align), 2);
    setSource(row(align, 0), host(host(infH)));
    setSource(row(align, 1), host(host(infV)));

    // extend alignment and obtain longest contained eps-match
    // TODO: something is wrong here, e.g. extract around seed, but also something else
    if (!_extendAndExtract(bandedAlign, scoreDropOff, scoreMatrix, infH, infV, EXTEND_BOTH, minLength, eps, align, verification_runtime.extension_time))
        return;

    // insert eps-match in matches string
    onAlignmentResult(align);
}

} // namespace dream_stellar
