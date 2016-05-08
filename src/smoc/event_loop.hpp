#pragma once

#include <boost/asio/io_service.hpp>
#include <boost/noncopyable.hpp>
#include <memory>

namespace smoc {

class event_loop : boost::noncopyable {
public:
  event_loop() = default;
  virtual ~event_loop() = default;

  auto &service() { return service_; }
  const auto &service() const { return service_; }

  void run();

  template<class T>
  void post(T t) { service_.dispatch(t); }

  void quit();

private:
  boost::asio::io_service service_;
  std::unique_ptr<boost::asio::io_service::work> work_;
};

} // smoc
