#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

#include "bruteforcetask.hpp"
#include "ns26.hpp"
#include "threadpool.hpp"

using namespace std;
using namespace BF;

void password_founded(string_view sv);


int main() {
  using namespace BF;

  RangeNumber main_rn {
    "aaaaa"_ns26,
    "a00000"_ns26
  };

  const auto n_chunks = std::thread::hardware_concurrency();

  auto sub_rn = std::vector<RangeNumber>(n_chunks);
  split_on_chunks(main_rn, n_chunks, begin(sub_rn));

  auto pool = ThreadPool{ n_chunks };

  cout << "start brute force . . .\n\n";

  for (const RangeNumber& rn : sub_rn) {
    auto task = BruteforceTask{ rn, password_founded };

    pool.add_task(move(task));
  }

  pool.wait_all();

  cout << "\nBrute froce finished\n";
  
  return 0;
}


void password_founded(string_view sv) {
  static auto mtx = mutex{};

  auto lg = lock_guard{ mtx };

  cout << "Founded: " << sv << '\n';
}

