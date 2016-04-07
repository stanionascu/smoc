#pragma once

#include <tuple>
#include <cassert>
#include <utility>

#include <boost/any.hpp>
#include <boost/type_index.hpp>

namespace smoc {

struct method {
  using type_index = boost::typeindex::type_index;

  template <class R, class C, class... Args>
  method(const std::string &name, R (C::*fptr)(Args...))
      : name_(name), fptr_(fptr), type_{boost::typeindex::type_id<R>()}, args_types_{boost::typeindex::type_id<Args>()...} {}

  template <class R, class C, class... Args>
  method(const std::string &name, R (C::*fptr)(Args...) const)
      : name_(name), fptr_(fptr), type_{boost::typeindex::type_id<R>()}, args_types_{boost::typeindex::type_id<Args>()...}, is_const_(true) {}

  const auto &name() const { return name_; }

  template <class R, class... Args> bool is_type_of() {
    return (boost::typeindex::type_id<R>() == type_ &&
            std::vector<type_index>{boost::typeindex::type_id<Args>()...} ==
            args_types_);
  }

  template <class R, class... Args, class C>
  R invoke(C *obj, Args... args) {
    if (is_const_)
      return invoke_impl<R>(obj, boost::any_cast<R(C::*)(Args...)const>(&fptr_),
                         args...);
    return invoke_impl<R>(obj, boost::any_cast<R(C::*)(Args...)>(&fptr_),
                       args...);
  }

  const auto &type() const { return type_; }
  const auto &arg_types() const { return args_types_; }
  auto arg_count() const { return args_types_.size(); }
  auto is_const() const { return is_const_; }

private:
  template<class R, class C, class F, class... Args>
  R invoke_impl(C *obj, F f, Args... args) {
    assert(f);
    return (*obj.**f)(args...);
  }

  std::string name_;
  boost::any fptr_;
  const type_index type_;
  const std::vector<type_index> args_types_;
  bool is_const_ = false;
};

}
