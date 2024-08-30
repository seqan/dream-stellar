#pragma once

#include <span>
#include <ranges>
#include <algorithm>

namespace std
{

// https://brevzin.github.io/c++/2020/03/30/span-comparisons/
template <typename R, typename T>
concept const_contiguous_range_of =
    ranges::contiguous_range<R const> &&
    same_as<
        remove_cvref_t<T>,
        ranges::range_value_t<R const>>;

namespace std {
  template <equality_comparable T, size_t E,
            const_contiguous_range_of<T> R>
  bool operator==(span<T, E> lhs, R const& rhs)
  {
    return ranges::equal(lhs, rhs);
  }

  template <three_way_comparable T, size_t E,
            const_contiguous_range_of<T> R>
  auto operator<=>(span<T, E> lhs, R const& rhs)
  {
    return lexicographical_compare_three_way(
        lhs.begin(), lhs.end(),
        ranges::begin(rhs), ranges::end(rhs));
  }
}

} // namespace std
