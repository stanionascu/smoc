#pragma once

#include <tuple>
#include <cassert>
#include <utility>

#include <boost/any.hpp>

namespace smoc {

struct method {
  template <class R, class C, class... Args>
  method(const std::string &name, R (C::*fptr)(Args...))
      : name_(name), fptr_(fptr), arg_count_(sizeof...(Args)) {}

  template <class R, class C, class... Args>
  method(const std::string &name, R (C::*fptr)(Args...) const)
      : name_(name), fptr_(fptr), arg_count_(sizeof...(Args)), is_const_(true) {}


  const auto &name() const { return name_; }

  template <class R, class C, class... Args> bool is_type_of() {
    if (is_const_)
      return boost::any_cast<R (C::*)(Args...) const>(&fptr_);
    return boost::any_cast<R (C::*)(Args...)>(&fptr_);
  }

  template <class R, class... Args, class C>
  R invoke(C *obj, Args... args) {
    if (is_const_)
      return invoke_impl<R>(obj, boost::any_cast<R(C::*)(Args...)const>(&fptr_),
                         args...);
    return invoke_impl<R>(obj, boost::any_cast<R (C::*)(Args...)>(&fptr_),
                       args...);
  }

  auto arg_count() const { return arg_count_; }
  auto is_const() const { return is_const_; }

private:
  template<class R, class C, class F, class... Args>
  R invoke_impl(C *obj, F f, Args... args) {
    assert(f);
    return (*obj.**f)(args...);
  }

  std::string name_;
  boost::any fptr_;
  size_t arg_count_;
  bool is_const_ = false;
};

}
