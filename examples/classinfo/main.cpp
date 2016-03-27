#include <iostream>

#include <smoc/object.hpp>

class my_class : public smoc::object {
  SMOC_OBJECT(my_class)
public:
  my_class() { }

  static smoc::property<int> foo;
  static smoc::property<std::string> name;

private:
  std::string name_ = "name_property";
  int foo_ = 34;
};

smoc::property<int> my_class::foo{&my_class::foo_};
smoc::property<std::string> my_class::name{&my_class::name_};

SMOC_DESCRIBE(my_class, (("Foo")(my_class::foo))(("Name")(my_class::name)))

int main(int argc, char **argv) {
  (void)argc; (void)argv;

  my_class test;
  std::cout << "Class name: " << test.info().class_name() << std::endl
            << "Static class name: " << my_class::static_info().class_name()
            << std::endl;
  std::cout << "List of properties: " << std::endl;
  for (auto &p : my_class::static_info().properties()) {
    std::cout << "\t" << p.first << " => ";
    if (p.second.type_id() == boost::typeindex::type_id<int>())
      std::cout << p.second.as<int>().read(&test);
    else if (p.second.type_id() == boost::typeindex::type_id<std::string>())
      std::cout << p.second.as<std::string>().read(&test);
    std::cout << std::endl;
  }

  return 0;
}
