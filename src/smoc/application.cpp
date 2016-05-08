#include "application.hpp"

namespace smoc {

struct application::pimpl {
  int exit_code_ = 0;
};

application::application() :
    d_(std::make_unique<application::pimpl>()) {
}

application::~application() {
}

int application::exec() {
  loop_.run();
  return d_->exit_code_;
}

void application::quit(int code) {
  d_->exit_code_ = code;
  loop_.quit();
}

}