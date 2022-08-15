#pragma once

#include "rangenumber.hpp"

namespace BF {
  
template <class OutputIt>
constexpr OutputIt split_on_chunks(const RangeNumber& rn, std::size_t n_chunk, OutputIt out_it) {
  const auto numbers_in_range = std::size_t{ rn.end - rn.start };

  const auto min_chunk_size = std::size_t{ numbers_in_range / n_chunk };
  auto n_chunks_aprox_size = std::size_t{ numbers_in_range % n_chunk };

  auto next_range_start = rn.start;

  for (auto i = std::size_t{ 0 }; i < n_chunk; ++i) {
    auto sub_rn = RangeNumber{
      next_range_start,
      next_range_start + min_chunk_size - 1
    };

    if (n_chunks_aprox_size > 0) {
      ++sub_rn.end;
      --n_chunks_aprox_size;
    }

    next_range_start = sub_rn.end + 1;
    *out_it++ = sub_rn;
  }

  return out_it;
}

} // namespace BF