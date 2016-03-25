#include "object.hpp"

namespace smoc {

object::object() {
}

object::~object() {
}

const object_info<object> &object::static_info() {
  static object_info<object> info;
  return info;
}

}
