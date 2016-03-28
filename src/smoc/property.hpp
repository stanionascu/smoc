#pragma once

#include <memory>
#include <string>
#include <cassert>

#include <boost/type_index.hpp>
#include <boost/any.hpp>

namespace smoc {

struct property {
  template <class T, class C>
  property(const std::string &name, T(C::*v))
      : name_(name), value_(v) {}
  virtual ~property() {}

  const std::string &name() const { return name_; }
  boost::any &value() { return value_; }
  const boost::any &value() const { return value_; }

  const auto &type() const { return value_.type(); }

  template<class T, class C>
  bool is_type_of() const {
    return (boost::any_cast<T(C::*)>(&value_));
  }

  template<class T, class C>
  const T &read(const C *obj) const {
    const auto &v = boost::any_cast<T(C::*)>(&value_);
    assert(v);
    return (*obj).**v;
  }

  template<class T, class C>
  void write(C *obj, const T &val) {
    auto v = boost::any_cast<T(C::*)>(&value_);
    assert(v);
    (*obj).**v = val;
  }

private:
  std::string name_;
  boost::any value_;
};

} // smoc
