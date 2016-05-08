#pragma once

#include <thread>
#include <atomic>

#include "event_loop.hpp"

namespace smoc {

class thread {
public:
  thread() = default;
  virtual ~thread() = default;

  auto id() const { return thread_.get_id(); }
  bool is_running() const { return is_running_ || thread_.joinable(); }

  void start() { thread_ = std::thread(&thread::run_impl, this); }
  void quit() { loop_.quit(); }
  void wait() {
    if (thread_.joinable())
      thread_.join();
  }

  template<class T>
  void post(T t) { loop_.post(t); }

protected:
  virtual void run() { loop_.run(); }

private:
    void run_impl();

private:
  std::atomic_bool is_running_{false};
  std::thread thread_;
  event_loop loop_;
};

} // smoc
