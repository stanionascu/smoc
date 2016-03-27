#include "object.hpp"

namespace smoc {

object_info<object> object::info_;

object::object() {
}

object::~object() {
}

const object_info<object> &object::static_info() {
  return info_;
}

}
