#include "ns26.hpp"

#include <cmath>
#include <algorithm>
#include <stdexcept>

namespace BF {

using namespace std;

auto NS26::to_str(size_t value) -> string {
  if (value == 0)
    return "0";

  const auto n_digits = static_cast<size_t>(log(value) / log(N)) + 1;

  auto result = string{};
  result.reserve(n_digits);

  while (value != 0) {
    result += base[value % N];
    value /= N;
  }

  reverse(result.begin(), result.end());

  return result;
}

auto NS26::to_value(string_view sv) -> size_t{
  auto value = size_t{ 0 };

  for (const char c : sv) {
    const auto first = begin(base);
    const auto last = end(base);

    auto it = find(first, last, c);

    if (it == last)
      throw runtime_error("Incorrect digit");

    value *= N;
    value += distance(first, it);
  }

  return value;
}

auto operator "" _ns26 (const char *s, size_t len) -> size_t{
  return NS26::to_value(string_view(s, len));
}


} // namespace BF