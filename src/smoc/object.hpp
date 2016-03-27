#pragma once

#include <string>
#include <vector>
#include <functional>
#include <map>

#include <boost/type_index.hpp>
#include <boost/preprocessor/seq/for_each.hpp>

#include "property.hpp"
#include "detail/object_macros.hpp"

#define SMOC_OBJECT(CLASS_NAME)                                                \
public:                                                                        \
  static const smoc::object_info<CLASS_NAME> &static_info();                   \
  const smoc::object_info_base &info() const override {                        \
    return CLASS_NAME::static_info();                                          \
  }

#define SMOC_DESCRIBE(CLASS_NAME, PROPERTIES)                                  \
  namespace smoc {                                                             \
  template <> object_info<CLASS_NAME> init_object_info<CLASS_NAME>() {         \
    object_info<my_class> info;                                                \
    info.properties_ = SMOC_PP_SEQ_TO_MAP(PROPERTIES);                         \
    return info;                                                               \
  }                                                                            \
  }                                                                            \
  const smoc::object_info<CLASS_NAME> &CLASS_NAME::static_info() {             \
    static const auto &info = smoc::init_object_info<CLASS_NAME>();            \
    return info;                                                               \
  }

namespace smoc {

struct object_info_base {
  virtual const std::string &class_name() const = 0;
  virtual std::map<std::string, property_base &> properties() const = 0;
};

template<class T>
struct object_info : object_info_base {
  const std::string &class_name() const override {
    static const std::string &name =
        boost::typeindex::type_id<T>().pretty_name();
    return name;
  }

  std::map<std::string, property_base &> properties() const override {
    return properties_;
  }

  std::map<std::string, property_base&> properties_;
};

class object {
public:
  object();
  virtual ~object();

  virtual const object_info_base &info() const { return object::static_info(); }
  static const object_info<object> &static_info();

private:
  static object_info<object> info_;

  std::map<std::string, property_base&> properties_;
};

template<class T>
object_info<T> init_object_info();

} // smoc
