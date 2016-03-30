#include "object.hpp"

namespace smoc {

object_info<object> object::info_;

template <>
const std::vector<method> object_info<object>::registerMethods{};

template <>
const std::vector<property> object_info<object>::registerProperties{};

object::object() {
}

object::~object() {
}

const object_info<object> &object::static_info() {
  return info_;
}

}
