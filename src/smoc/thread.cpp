#include "thread.hpp"

namespace smoc {

void thread::run_impl() {
  is_running_ = true;
  run();
  is_running_ = false;
}

} // smoc