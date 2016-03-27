#pragma once

#include <memory>

#include <boost/type_index.hpp>

#include "detail/property_data.hpp"

namespace smoc {

template<class Type>
struct property;

struct property_base {
  virtual const boost::typeindex::type_index &type_id() const = 0;
  template <class Type> property<Type> &as() {
    return static_cast<property<Type> &>(*this);
  }
  template <class Type> const property<Type> &as() const {
    return static_cast<const property<Type> &>(*this);
  }
};

template<class Type>
struct property : property_base {
  // class attribute property
  template<class C>
  property(Type (C::*ptr), C *obj = nullptr) :
      d_(std::make_unique<detail::property_attribute_data<Type, C>>(ptr, obj))
  {
  }

  const boost::typeindex::type_index &type_id() const override {
    static const auto &id =
        boost::typeindex::type_id<Type>();
    return id;
  }

  operator Type() { return d_->get(); }
  const Type &operator()() { return d_->get(); }
  auto &operator=(const Type &v) { d_->set(v); return *this; }

  template<class C>
  const Type &read(const C *obj) const {
    return static_cast<const detail::property_attribute_data<Type, C> *>(
               d_.get())
        ->read(obj);
  }

  template<class C>
  void write(C *obj, const Type &v) {
    static_cast<detail::property_attribute_data<Type, C> *>(d_.get())->write(
        obj, v);
  }

private:
  std::unique_ptr<detail::property_data<Type>> d_;
};

} // smoc
