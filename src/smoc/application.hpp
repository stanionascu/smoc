#pragma once

#include "event_loop.hpp"

namespace smoc {

class application : boost::noncopyable {
public:
  application();
  virtual ~application();

  int exec();
  void quit(int code = 0);

  template<class T>
  void post(T t) { loop_.post(t); }

private:
  struct pimpl;
  std::unique_ptr<pimpl> d_;
  smoc::event_loop loop_;
};

} // smoc