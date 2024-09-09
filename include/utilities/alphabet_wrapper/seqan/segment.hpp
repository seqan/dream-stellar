#pragma once

#include <seqan/sequence/segment_base.h>

namespace seqan2
{

template <typename TAlphabet, typename TPos>
TAlphabet value(seqan2::Segment<seqan2::Segment<std::span<TAlphabet const> const, InfixSegment>, InfixSegment> const & me,
                TPos pos)
{
    assert(pos >= 0);
    auto const & host_span = *me.data_host.data_host;
    assert(me.data_host.data_host);
    assert(pos + seqan2::beginPosition(me) < host_span.size());
    return host_span[seqan2::beginPosition(me) + pos];
}

template <typename TScore, typename TAlphabet, typename TPos>
TAlphabet value(TScore const & /* Score matrix to avoid ambiguity in overloading */,
                seqan2::Segment<seqan2::Segment<std::span<TAlphabet const> const, InfixSegment>, InfixSegment> const & me,
                TPos pos)
{
    assert(pos >= 0);
    auto const & host_span = *me.data_host.data_host;
    assert(me.data_host.data_host);
    assert(pos + seqan2::beginPosition(me) < host_span.size());
    return host_span[seqan2::beginPosition(me) + pos];
}

template <typename TScore, typename TAlphabet, typename TPosition>
inline TAlphabet sequenceEntryForScore(TScore const & /*scoringScheme*/, 
                                       Segment<Segment<std::span<TAlphabet const> const, InfixSegment>, InfixSegment> const & seq, 
                                       TPosition pos)
{
    return value(seq, pos);
}

} // namespace seqan2
