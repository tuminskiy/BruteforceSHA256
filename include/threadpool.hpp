#pragma once

#include <unordered_set>
#include <cstdint>
#include <future>
#include <vector>
#include <queue>
#include <mutex>

namespace BF {

class ThreadPool final {
  using Id = std::uint64_t;
  using TaskWithId = std::pair<std::future<void>, Id>;
  using QueueTask = std::queue<TaskWithId>;
  using CompletedTasks = std::unordered_set<Id>;
  using Threads = std::vector<std::thread>;

public:
  explicit ThreadPool(std::size_t max_threads);
  ~ThreadPool();

  template <class Func, class... Args>
  auto add_task(const Func& task_func, Args&&... args) -> Id;

  auto wait(Id task_id) -> void;
  auto wait_all() -> void;

  auto calculated(Id task_id) -> bool;

private:
  auto run() -> void;

private:
  QueueTask m_tasks;
  std::mutex m_tasks_mtx;
  std::condition_variable m_tasks_cv;

  CompletedTasks m_completed;
  std::mutex m_completed_mtx;
  std::condition_variable m_completed_cv;

  Threads m_threads;
  std::atomic<bool> m_finished;

  std::atomic<Id> m_last_id;
};

} // namespace BF

#include "detail/threadpool_impl.hpp"