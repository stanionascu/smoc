#pragma once

namespace smoc { namespace detail {

template<class Type>
struct property_data {
  virtual const Type &get() const = 0;
  virtual void set(const Type &v) = 0;
};

template<class Type, class C>
struct property_attribute_data : property_data<Type> {
  property_attribute_data(Type (C::*attr), C *obj) :
      obj_(obj), attr_(attr)
  {
  }

  const Type &get() const override { return obj_->*attr_; }
  void set(const Type &v) override { obj_->*attr_ = v; }

  const Type &read(const C *obj) const { return obj->*attr_; }
  void write(C *obj, const Type &v) { obj->*attr_ = v; }

  C *obj_;
  Type (C::*attr_);
};

} } // smoc::detail
