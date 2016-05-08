#include "event_loop.hpp"

namespace smoc {

void event_loop::run() {
  work_ = std::make_unique<boost::asio::io_service::work>(service_);
  service_.run();
}

void event_loop::quit() {
  work_.reset();
}

} // smoc
