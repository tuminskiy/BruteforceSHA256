#include "bruteforcetask.hpp"
#include "ns26.hpp"
#include "sha256.hpp"

#include <set>
#include <iostream>

namespace BF {

using namespace std;

BruteforceTask::BruteforceTask(const RangeNumber& rn, const Callback& callback)
  : m_rn{ rn }
  , m_callback{ callback }
{ }


void BruteforceTask::operator() () const {
  for (auto i = m_rn.start; i < m_rn.end; ++i) {
    const auto password = NS26::to_str(i);
    const auto hash = to_sha256_hex(password);
    
    if (is_required_hash(hash)) {
      m_callback(password);
      return;
    }
  }
}


auto BruteforceTask::to_sha256_hex(string_view sv) -> string {
  SHA256 sha256;

  sha256.update(sv.data());
  auto digist = sha256.digest();
  auto result = sha256.to_string(digist);

  return result;
}


auto BruteforceTask::is_required_hash(string_view hash) -> bool {
  using namespace std::string_view_literals;

  static const set<string_view> sha256s = {
    "3a7bd3e2360a3d29eea436fcfb7e44c735d117c42d1c1835420b6b9942dd4f1b"sv, // apple
    "e45d90957eec7387726c6a1b174da7b566a24ff4cb060dcbcdfebb931a93ffe3"sv, // passw
    "560d4dfa710b12897e058a6f4a7a44c9882193fcbf722fbc9e44622386a9518c"sv  // mingw
  };

  return sha256s.find(hash) != sha256s.end();
}

} // namespace BF