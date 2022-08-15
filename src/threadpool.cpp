#include "threadpool.hpp"

namespace BF {

using namespace std;

ThreadPool::ThreadPool(size_t max_threads)
  : m_tasks{}, m_tasks_mtx{}, m_tasks_cv{}
  , m_completed{}, m_completed_mtx{}, m_completed_cv{}
  , m_threads{}, m_finished{ false }
  , m_last_id{ 0 } {

  m_threads.reserve(max_threads);
  for (size_t i = 0; i < max_threads; ++i) {
    m_threads.emplace_back(&ThreadPool::run, this);
  }
}


ThreadPool::~ThreadPool() {
  m_finished = true;

  for (auto& thread : m_threads) {
    m_tasks_cv.notify_all();
    thread.join();
  }
}


auto ThreadPool::run() -> void {
  while (!m_finished) {
    auto ul = unique_lock{ m_tasks_mtx };

    m_tasks_cv.wait(ul, [this] {  return !m_tasks.empty() || m_finished; } );

    if (!m_tasks.empty()) {
      auto task_with_id = move(m_tasks.front());
      m_tasks.pop();
      ul.unlock();

      auto& [task, id] = task_with_id;
      task.get();

      auto lg = lock_guard{ m_completed_mtx };

      m_completed.insert(id);

      m_completed_cv.notify_all();
    }
  }
}


auto ThreadPool::wait(Id task_id) -> void {
  auto ul = unique_lock{ m_completed_mtx };

  m_completed_cv.wait(ul, [this, task_id] { 
    return m_completed.find(task_id) != m_completed.end();
  });
}


auto ThreadPool::wait_all() -> void {
  auto ul = unique_lock{ m_tasks_mtx };

  m_completed_cv.wait(ul, [this] {
    auto lg = lock_guard{ m_completed_mtx };
    return m_tasks.empty() && m_last_id == m_completed.size();
  });
}


auto ThreadPool::calculated(Id task_id) -> bool {
  auto lg = lock_guard{ m_completed_mtx };

  return m_completed.find(task_id) != m_completed.end();
}

} // namespace BF
