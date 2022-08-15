#pragma once

#include <string>

namespace BF {

class NS26 {
  static constexpr char base[] = "0abcdefghijklmnopqrstuvwxyz";
  static constexpr std::size_t N = std::size(base) - 1;

public:
  static auto to_str(std::size_t value) -> std::string;

  static auto to_value(std::string_view sv) -> std::size_t;
};

std::size_t operator "" _ns26 (const char *s, std::size_t len);

} // namespace BF