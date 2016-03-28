#include <iostream>

#include <smoc/object.hpp>

class my_class : public smoc::object {
  SMOC_OBJECT(my_class)
public:
  my_class() { }

private:
  std::string name_ = "name_property";
  int foo_ = 34;
};

SMOC_DESCRIBE(my_class, (("Foo")(&my_class::foo_))(("Name")(&my_class::name_)))

int main(int argc, char **argv) {
  (void)argc; (void)argv;

  my_class test;
  std::cout << "Class name: " << test.info().class_name() << std::endl
            << "Static class name: " << my_class::static_info().class_name()
            << std::endl;
  std::cout << "Writing 77 into Foo property" << std::endl;
  my_class::static_info().properties()[0].write<int>(&test, 77);
  std::cout << "List of properties: " << std::endl;
  for (const auto &p : my_class::static_info().properties()) {
    std::cout << "\t" << p.name() << " => ";
    if (p.is_type_of<std::string, my_class>())
      std::cout << p.read<std::string>(&test);
    if (p.is_type_of<int, my_class>())
      std::cout << p.read<int>(&test);
    std::cout << std::endl;
  }

  return 0;
}
