#pragma once

#include <cstddef>

namespace BF {

struct RangeNumber {
  std::size_t start;
  std::size_t end;
};


template <class OutputIt>
constexpr auto split_on_chunks(const RangeNumber& rn, std::size_t n_chunk, OutputIt out_it) -> OutputIt;

} // namespace BF

#include "detail/rangenumber_impl.hpp"