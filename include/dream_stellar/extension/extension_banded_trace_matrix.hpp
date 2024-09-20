
#pragma once

#include <span>

#include <seqan/sequence.h>
#include <seqan/align/align_traceback.h> // needs seqan/sequence.h

namespace dream_stellar
{

struct extension_banded_trace_matrix
{
    using diagonal_t = std::make_signed_t<size_t>;

    extension_banded_trace_matrix(
        size_t const rowCount,
        size_t const columnCount,
        diagonal_t const lowerDiagonal,
        diagonal_t const upperDiagonal
    ) :
        _rowCount{rowCount},
        _columnCount{columnCount},
        _lowerDiagonal{lowerDiagonal},
        _upperDiagonal{upperDiagonal},
        _traceMatrix{}
    {
        assert(lowerDiagonal <= upperDiagonal);

        resize(_traceMatrix, dataSize());
    }

    size_t rows() const
    {
        return _rowCount;
    }

    size_t columns() const
    {
        return _columnCount;
    }

    diagonal_t lowerDiagonal() const
    {
        return _lowerDiagonal;
    }

    diagonal_t upperDiagonal() const
    {
        return _upperDiagonal;
    }

    size_t diagonalWidth() const
    {
        return _upperDiagonal - _lowerDiagonal + 1;
    }

    // memory region for active row
    std::span<seqan2::TraceBack> rowSpan(size_t const row)
    {
        auto [beginRow, endRow] = rowInterval();
        if (!(beginRow <= row && row <= endRow))
            return {};

        size_t rowOffset = row - beginRow;
        auto diagonalInterval = diagonalIntervalInRow(row);
        size_t columnBegin = std::min(diagonalInterval.first + _lowerDiagonal + row, _columnCount);
        size_t columnEnd = std::min(diagonalInterval.second + _lowerDiagonal + row, _columnCount);

        return data().subspan(
            rowOffset * diagonalWidth() + diagonalInterval.first,
            columnEnd - columnBegin);
    }

    // complete underlying data
    std::span<seqan2::TraceBack> data()
    {
        seqan2::TraceBack & firstValue = *begin(_traceMatrix);
        return {&firstValue, dataSize()};
    }

    seqan2::String<seqan2::TraceBack> & underlyingTraceMatrix()
    {
        return _traceMatrix;
    }

    size_t dataSize() const
    {
        std::pair<size_t, size_t> pair = rowInterval();
        size_t height = pair.second - pair.first;
        return height * diagonalWidth();
    }

    std::pair<size_t, size_t> rowInterval() const
    {
        size_t const rowBegin = (_upperDiagonal <= 0) ? -_upperDiagonal : 0;
        size_t const rowEnd = [&]()
        {
            size_t const maxRowEnd = _rowCount;
            assert ((diagonal_t)_columnCount >= _lowerDiagonal);
            if (_columnCount - _lowerDiagonal < maxRowEnd)
                return _columnCount - _lowerDiagonal;
            else
                return maxRowEnd;
        }();

        return {rowBegin, rowEnd};
    }

    std::pair<size_t, size_t> diagonalIntervalInRow(size_t const row) const
    {
        size_t const rowOffset = row - rowInterval().first;

        size_t diagonalEnd = diagonalWidth();
        size_t diagonalBegin = 0;
        if (_lowerDiagonal <= 0)
        {
            diagonalBegin = (_upperDiagonal < 0) ? diagonalEnd : (size_t) (1 - _lowerDiagonal);
        }

        // subtract in each row iteration
        // if (diagonalBegin > 0) --diagonalBegin;

        size_t const diagonalBeginOffset = std::min(rowOffset + 1, diagonalBegin);
        diagonalBegin -= diagonalBeginOffset; // lo_diag

        // subtract in each row iteration
        // if ((diagonal_t)actualRow >= (diagonal_t)len1 - diagU) --hi_diag;
        size_t const diagonalEndOffset =
            ((diagonal_t)row >= (diagonal_t)_columnCount - _upperDiagonal) ?
            (row - _columnCount + _upperDiagonal) :
            0;
        diagonalEnd -= diagonalEndOffset; // hi_diag

        return {diagonalBegin, diagonalEnd};
    }

    std::pair<size_t, size_t> columnIntervalInRow(size_t const row) const
    {
        auto diagonal = diagonalIntervalInRow(row);

        size_t columnBegin = std::min(diagonal.first + _lowerDiagonal + row, _columnCount);
        size_t columnEnd = std::min(diagonal.second + _lowerDiagonal + row, _columnCount);

        return {columnBegin, columnEnd};
    }

private:
    size_t _rowCount;
    size_t _columnCount;
    diagonal_t _lowerDiagonal;
    diagonal_t _upperDiagonal;

    seqan2::String<seqan2::TraceBack> _traceMatrix;
};

}
