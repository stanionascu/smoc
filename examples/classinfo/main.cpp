#include <iostream>

#include <smoc/object.hpp>

class my_class : public smoc::object {
  SMOC_OBJECT(my_class)
public:
  my_class() {
  }
};

int main(int argc, char **argv) {
  (void)argc; (void)argv;

  my_class test;
  std::cout << "Class name: " << test.info().class_name() << std::endl
            << "Static class name: " << my_class::static_info().class_name()
            << std::endl;

  return 0;
}
