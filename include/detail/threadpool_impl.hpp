#pragma once

#include "threadpool.hpp"

namespace BF {

template <class Func, class... Args>
auto ThreadPool::add_task(const Func& task_func, Args&&... args) -> Id {
  auto task_id = m_last_id++;

  auto lg = std::lock_guard{ m_tasks_mtx };
  
  m_tasks.emplace(std::async(std::launch::deferred, task_func, args...), task_id);

  m_tasks_cv.notify_one();

  return task_id;
}

} // namespace BF