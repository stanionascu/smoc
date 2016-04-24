#include <gtest/gtest.h>

#include <smoc/object.hpp>

class test_object : public smoc::object {
  SMOC_OBJECT(test_object)
};

template<>
const std::vector<smoc::property> smoc::object_info<test_object>::registerProperties{};

template<>
const std::vector<smoc::method> smoc::object_info<test_object>::registerMethods{};

TEST(object_test, static_object_info) {
  EXPECT_EQ(test_object::static_info().class_name(),
            "test_object");
}

TEST(object_test, object_info) {
  test_object to;
  EXPECT_EQ(to.info().class_name(),
            "test_object");
  EXPECT_EQ(to.info().class_name(),
            test_object::static_info().class_name());
}
