#pragma once

#include <memory>
#include <string>
#include <cassert>

#include <boost/type_index.hpp>
#include <boost/any.hpp>

namespace smoc {

struct property {
  using type_index = boost::typeindex::type_index;

  template <class T, class C>
  property(const std::string &name, T(C::*v))
      : name_(name), getter_(v), setter_(v), type_(boost::typeindex::type_id<T>()), read_only_(false), member_(false) {}

  template <class T, class C>
  property(const std::string &name, const T(C::*v))
      : name_(name), getter_(v), type_(boost::typeindex::type_id<T>()), read_only_(true), member_(false) {}

  template<class T, class C>
  property(const std::string &name, const T&(C::*getter)()const, void(C::*setter)(const T&) = nullptr)
      : name_(name), getter_(getter), setter_(setter), type_(boost::typeindex::type_id<T>()), member_(true)
  {
    read_only_ = setter_.empty();
  }

  virtual ~property() {}

  const std::string &name() const { return name_; }

  const auto &type() const { return type_; }

  template<class T>
  bool is_type_of() const {
    return type_ == boost::typeindex::type_id<T>();
  }

  template<class T, class C>
  const T read(const C *obj) const {
    if (member_) {
      return invoke_getter<T, C>(obj);
    } else if (read_only_) {
      return invoke_member<const T, C>(obj);
    }
    return invoke_member<T, C>(obj);
  }

  template<class T, class C>
  void write(C *obj, const T &val) {
    assert(!read_only_);
    if (member_) {
      invoke_setter<T, C>(obj, val);
    } else {
      auto v = boost::any_cast<T(C::*)>(&setter_);
      assert(v);
      (*obj).**v = val;
    }
  }

  bool is_read_only() const { return read_only_; }
  bool is_attribute() const { return !member_; }

private:
  template <class T, class C>
  const T invoke_getter(const C *obj) const {
    const auto &v = boost::any_cast<const T&(C::*)() const>(&getter_);
    assert(v);
    return ((*obj).**v)();
  }

  template <class T, class C>
  T invoke_member(const C *obj) const {
    const auto &v = boost::any_cast<T(C::*)>(&getter_);
    assert(v);
    return (*obj).**v;
  }

  template <class T, class C>
  void invoke_setter(C *obj, const T &val)
  {
    auto v = boost::any_cast<void(C::*)(const T&)>(&setter_);
    assert(v);
    ((*obj).**v)(val);
  }

  std::string name_;
  boost::any getter_;
  boost::any setter_;
  type_index type_;
  bool read_only_ = false;
  bool member_ = false;
};

} // smoc
