#pragma once

#include <seqan/align.h>

#include <dream_stellar/options/dream_options.hpp>
#include <dream_stellar/options/eps_match_options.hpp>
#include <dream_stellar/options/index_options.hpp>
#include <dream_stellar/options/verifier_options.hpp>
#include <dream_stellar/shared.hpp>

#if __cpp_designated_initializers || __GNUC__ >= 8
#   define STELLAR_DESIGNATED_INITIALIZER(designator, value) designator value
#else
#   define STELLAR_DESIGNATED_INITIALIZER(designator, value) value
#endif // __cpp_designated_initializers || __GNUC__ >= 8

namespace dream_stellar
{

using namespace seqan2;

struct StellarStatistics
{
    bool kMerComputed{};
    unsigned kMerLength{};
    unsigned smin{};
    int threshold{};
    int distanceCut{};
    int delta{};
    int overlap{};

    StellarStatistics(StellarOptions const & options)
    {
        if (!options.epsilon.is_proper())
            throw std::domain_error{"Epsilon must be between >= 0.0 and < 1.0."};

        size_t n0 = options.minLength; // min length
        size_t e0 = StellarOptions::absoluteErrors(options.epsilon, n0);
        // nearest length (after min length) that has exactly e0 + 1 many absolute errors
        size_t n1 = StellarOptions::minLengthWithExactError(e0 + 1, options.epsilon);
        size_t e1 = e0 + 1;

        unsigned smin0 = StellarOptions::pigeonholeLemma(n0, e0);
        unsigned smin1 = StellarOptions::pigeonholeLemma(n1, e1);
        smin = (unsigned) std::min(smin0, smin1);

        assert(n1 >= n0);
        assert(options.epsilon.numerator() == 0 || StellarOptions::absoluteErrors(options.epsilon, n1) == e1);

        kMerLength = options.qGram;
        kMerComputed = options.qGram == (size_t)-1;

        if (kMerComputed)
            kMerLength = std::min(std::max(1u, smin), 32u);

        if (kMerLength > (unsigned)options.minLength)
            throw std::domain_error{"qGram must be smaller than minLength."};

        size_t threshold0 = StellarOptions::kmerLemma(n0, kMerLength, e0);
        size_t threshold1 = StellarOptions::kmerLemma(n1, kMerLength, e1);
        threshold = std::max(size_t{1u}, std::min(threshold0, threshold1));

        overlap = (int) floor((2 * threshold + kMerLength - 3) / (1 / (double)options.epsilon - kMerLength));
        distanceCut = (threshold - 1) + kMerLength * overlap + kMerLength;
        int logDelta = _max(4, (int) ceil(log((double)overlap + 1) / log(2.0)));
        delta = 1 << logDelta;
    }
};

struct StellarComputeStatistics
{
    size_t numSwiftHits = 0;

    size_t maxLength = 0;
    size_t totalLength = 0;

    void mergeIn(StellarComputeStatistics const & statistics)
    {
        this->numSwiftHits += statistics.numSwiftHits;
        this->totalLength += statistics.totalLength;
        this->maxLength = std::max<size_t>(this->maxLength, statistics.maxLength);
    }
};

struct StellarOutputStatistics
{
    size_t maxLength{0u};
    size_t totalLength{0u};
    size_t numMatches{0u};
    size_t numDisabled{0u};

    void mergeIn(StellarOutputStatistics const & statistics)
    {
        maxLength = std::max(maxLength, statistics.maxLength);
        totalLength = totalLength + statistics.totalLength;
        numMatches = numMatches + statistics.numMatches;
        numDisabled = numDisabled + statistics.numDisabled;
    }
};

struct StellarComputeStatisticsCollection
{
    StellarComputeStatistics const & operator[](size_t const databaseRecordID) const
    {
        return _statistics[databaseRecordID];
    }

    void addStatistics(StellarComputeStatistics const & computeStatistics)
    {
        _statistics.push_back(computeStatistics);
    }

    size_t size() const
    {
        return _statistics.size();
    }
private:
    std::vector<StellarComputeStatistics> _statistics; // one per database
};


///////////////////////////////////////////////////////////////////////////////
// Container for storing a local alignment match
template<typename TSequence_ = std::span<seqan2::alphabet_adaptor<seqan3::dna4 const> const>, typename TId_ = std::string>
struct StellarMatch {
    static_assert(std::is_const<TSequence_>::value, "Sequence must be const qualified! I.e. StellarMatch<... const, ...>");
    typedef TSequence_                          TSequence;
    typedef TId_                                TId;
    
    //!TODO: can std::span<alphabet_t> be aligned
    /*
    if (std::same_as<TSequence_, std::span<seqan2::alphabet_adaptor<seqan3::dna4 const> const>>::value)
        typedef typename TSequence::size_type  TPos;
    else
        typedef typename Position<TSequence>::Type  TPos;
    */
    typedef size_t TPos;

    typedef Align<seqan2::String<seqan2::alphabet_adaptor<seqan3::dna4>>, ArrayGaps>         TAlign;
    typedef typename Row<TAlign>::Type         TRow;
    static const TId INVALID_ID;

    TId id;         // database ID
    bool orientation;
    TPos begin1;
    TPos end1;
    TRow row1;

    TPos begin2;
    TPos end2;
    TRow row2;

    StellarMatch() : id(), orientation(false), begin1(0), end1(0), begin2(0), end2(0)
    {}

    template <typename TAlign, typename TId>
    StellarMatch(TAlign & _align, TId _id, bool _orientation)
    {
        id = _id;
        orientation = _orientation;
        row1 = row(_align, 0);
        row2 = row(_align, 1);

        begin1 = beginPosition(row1);
        end1 = endPosition(row1);

        begin2 = beginPosition(row2);
        end2 = endPosition(row2);
    }
};

template <typename TSequence, typename TId>
const TId
StellarMatch<TSequence, TId>::INVALID_ID = "###########";

///////////////////////////////////////////////////////////////////////////////
// Container for storing local alignment matches of one query sequence
template<typename TMatch_>
struct QueryMatches {
    typedef typename TMatch_::TSequence::size_type TSize;

    std::vector<TMatch_> matches;
    bool disabled;

    QueryMatches() : disabled(false)
    {}
 
    inline bool removeOverlapsAndCompactMatches(size_t const minLength,
                                                size_t const disableThresh,
                                                size_t const compactThresh,
                                                size_t const numMatches)
    {
        if (this->disabled)
            return false;

        size_t const matchesCount = (this->matches).size();

        if (matchesCount > disableThresh) {
            this->disabled = true;
            (this->matches).clear();
            return false;
        }

        if (matchesCount <= compactThresh)
            return false;

        //!TODO: reimplement for std::vector
        //maskOverlaps(this->matches, minLength);      // remove overlaps and duplicates
        //compactMatches(this->matches, numMatches);   // keep only the <numMatches> longest matches
        return true;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // Appends a match to matches container and removes overlapping matches if threshold is reached.
    template<typename TSource, typename TId, typename TSize, typename TSize1>
    inline bool insertMatch(StellarMatch<TSource const, TId> const & match,
                             TSize const minLength,
                             TSize1 const disableThresh,
                             TSize1 & compactThresh,
                             TSize1 const numMatches) {

        matches.emplace_back(match);

        // std::cerr << "Inserting match \n-------------\n" << match.row1 <<"\n" << match.row2 << "----------------\n";

        if (removeOverlapsAndCompactMatches(minLength, disableThresh, compactThresh, numMatches))
        {
            // raise compact threshold if many matches are kept
            if ((matches.size() << 1) > compactThresh)
                compactThresh += (compactThresh >> 1);
        }
        return true;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // Appends a match to matches container and removes overlapping matches if threshold is reached.
    template<typename TId, typename TSize, typename TSize1>
    inline bool insertMatch(StellarMatch<seqan2::String<seqan2::alphabet_adaptor<seqan3::dna4>> const, TId> const & match,
                            TSize const minLength,
                            TSize1 const disableThresh,
                            TSize1 & compactThresh,
                            TSize1 const numMatches) {

        StellarMatch<std::span<seqan2::alphabet_adaptor<seqan3::dna4> const> const, std::string> backconverted_match{};
        backconverted_match.id = match.id;
        backconverted_match.orientation = match.orientation;
        backconverted_match.begin1 = match.begin1;
        backconverted_match.end1 = match.end1;
        backconverted_match.row1 = match.row1;
        
        backconverted_match.begin2 = match.begin2;
        backconverted_match.end2 = match.end2;
        backconverted_match.row2 = match.row2;

        matches.emplace_back(backconverted_match);

        // std::cerr << "Inserting match \n-------------\n" << match.row1 <<"\n" << match.row2 << "----------------\n";

        if (removeOverlapsAndCompactMatches(minLength, disableThresh, compactThresh, numMatches))
        {
            // raise compact threshold if many matches are kept
            if ((matches.size() << 1) > compactThresh)
                compactThresh += (compactThresh >> 1);
        }
        return true;
    }
};

///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// to sort matches by position and remove overlapping matches
template <typename TMatch>
struct LessPos : public ::std::function<bool(TMatch, TMatch)> {
    LessPos() {}

    inline int compare(TMatch const & a, TMatch const & b) const {
        // query number
        if ((a.id) < (b.id)) return -1;
        if ((a.id) > (b.id)) return 1;

        // database begin position
        typename TMatch::TPos aBegin1 = _min(a.begin1, a.end1);
        typename TMatch::TPos bBegin1 = _min(b.begin1, b.end1);
        if (aBegin1 < bBegin1) return -1;
        if (aBegin1 > bBegin1) return 1;

        // database end position
        typename TMatch::TPos aEnd1 = _max(a.begin1, a.end1);
        typename TMatch::TPos bEnd1 = _max(b.begin1, b.end1);
        if (aEnd1 < bEnd1) return -1;
        if (aEnd1 > bEnd1) return 1;

        // query begin position
        typename TMatch::TPos aBegin2 = _min(a.begin2, a.end2);
        typename TMatch::TPos bBegin2 = _min(b.begin2, b.end2);
        if (aBegin2 < bBegin2) return -1;
        if (aBegin2 > bBegin2) return 1;

        // query end position
        typename TMatch::TPos aEnd2 = _max(a.begin2, a.end2);
        typename TMatch::TPos bEnd2 = _max(b.begin2, b.end2);
        if (aEnd2 < bEnd2) return -1;
        if (aEnd2 > bEnd2) return 1;

        // orientation
        if (a.orientation > b.orientation) return -1;
        if (a.orientation < b.orientation) return 1;

        //// orientation
        //bool oa = a.begin1 < a.end1;
        //bool ob = b.begin1 < b.end1;
        //if (oa != ob) return oa;

        return 0;
    }

    inline bool operator() (TMatch const & a, TMatch const & b) const {
        return compare(a, b) == -1;
    }
};

///////////////////////////////////////////////////////////////////////////////
// to sort matches by length
template <typename TMatch>
struct LessLength : public ::std::function<bool(TMatch, TMatch)> {
    LessLength() {}

    inline int compare(TMatch const & a, TMatch const & b) const {
        if (a.id == TMatch::INVALID_ID) return 1;
        if (b.id == TMatch::INVALID_ID) return -1;

        typename TMatch::TPos aLength = abs((int)a.end1 - (int)a.begin1);
        typename TMatch::TPos bLength = abs((int)b.end1 - (int)b.begin1);

        if (aLength < bLength) return 1;
        if (aLength > bLength) return -1;

        return 0;
    }

    inline bool operator() (TMatch const & a, TMatch const & b) const {
        return compare(a, b) == -1;
    }
};

///////////////////////////////////////////////////////////////////////////////
// Determines whether match1 is upstream of match2 in specified row.
//  If matches overlap, the non-overlapping parts have to be longer than minLenght.
template<typename TSequence, typename TId, typename TRowNo, typename TSize>
inline bool
_isUpstream(StellarMatch<TSequence const, TId> & match1, StellarMatch<TSequence const, TId> & match2, TRowNo row, TSize minLength) {
    typedef typename StellarMatch<TSequence const, TId>::TPos TPos;

    TPos e1, b2;
    if (row == 0) {
        e1 = match1.end1;
        b2 = match2.begin1;
    } else {
        e1 = match1.end2;
        b2 = match2.begin2;
    }

    if (e1 <= b2) return true;

    TPos b1, e2;
    if (row == 0) {
        e2 = match2.end1;
        b1 = match1.begin1;
    } else {
        e2 = match2.end2;
        b1 = match1.begin2;
    }

    if (b1 < b2 && (b2 - b1 >= minLength)) {
        if ((e1 < e2) && (e2 - e1 >= minLength)) return true;
    }

    return false;
}

///////////////////////////////////////////////////////////////////////////////
// sorts StellarMatchees by specified functor
template <typename TSequence, typename TId, typename TFunctorLess>
inline void
sortMatches(String<StellarMatch<TSequence const, TId> > & stellarMatches, TFunctorLess const & less) {
    std::stable_sort(
        begin(stellarMatches, Standard()),
        end(stellarMatches, Standard()),
        less);
}

///////////////////////////////////////////////////////////////////////////////
// returns the length of the longer row from StellarMatch
template <typename TSequence, typename TId>
inline typename Size<TSequence const>::Type
length(StellarMatch<TSequence const, TId> & match) {
    return _max(length(match.row1), length(match.row2));
}

} // namespace dream_stellar
