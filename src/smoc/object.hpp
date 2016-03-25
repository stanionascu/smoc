#pragma once

#include <string>

#include <boost/type_index.hpp>

#define SMOC_OBJECT(CLASS_NAME)                                                \
public:                                                                        \
  static const smoc::object_info<CLASS_NAME> &static_info() {                  \
    static const smoc::object_info<CLASS_NAME> info;                           \
    return info;                                                               \
  }                                                                            \
  const smoc::object_info_base &info() const override {                        \
    return CLASS_NAME::static_info();                                          \
  }

namespace smoc {

struct object_info_base {
  virtual const std::string &class_name() const = 0;
};

template<class T>
struct object_info : object_info_base {
  const std::string &class_name() const override {
    static const std::string &name =
        boost::typeindex::type_id<T>().pretty_name();
    return name;
  }
};

class object {
public:
  object();
  virtual ~object();

  virtual const object_info_base &info() const { return object::static_info(); }
  static const object_info<object> &static_info();

private:
  object_info<object> info_;
};

} // smoc
