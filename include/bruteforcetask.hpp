#pragma once

#include <string_view>
#include <functional>

#include "rangenumber.hpp"

namespace BF {


class BruteforceTask {
public:
  using Callback = std::function<void(std::string_view)>;

  explicit BruteforceTask(const RangeNumber& rn, const Callback& callback);

  void operator() () const;

private:
  static auto to_sha256_hex(std::string_view sv) -> std::string;

  static auto is_required_hash(std::string_view hash) -> bool;

private:
  RangeNumber m_rn;
  Callback m_callback;
};


} // namespace BF