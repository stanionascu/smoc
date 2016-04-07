#include <iostream>

#include <smoc/object.hpp>
#include <chrono>

class my_class : public smoc::object {
  SMOC_OBJECT(my_class)
public:
  my_class() { }

  void say_hello() {
    std::cout << "hello...";
  }

  void say(const std::string &word) {
    last_said_word_ = word;
    std::cout << word << "...";
  }

  bool is_last_word_said() const {
    return !last_said_word_.empty();
  }

  const int &get_foo() const { return foo_; }
  void set_foo(const int &v) { foo_ = v; }

private:
  std::string name_ = "name_property";
  int foo_ = 34;
  const int const_foo_ = 88;
  std::string last_said_word_;
};

template <>
const std::vector<smoc::method> smoc::object_info<my_class>::registerMethods{
  { "say_hello", &my_class::say_hello },
  { "say", &my_class::say },
  { "is_last_word_said", &my_class::is_last_word_said }
};
template <>
const std::vector<smoc::property> smoc::object_info<my_class>::registerProperties{
  { "foo", &my_class::foo_ },
  { "name", &my_class::name_ },
  { "const_foo", &my_class::const_foo_ },
  { "foo_setget", &my_class::get_foo, &my_class::set_foo}
};

int main(int argc, char **argv) {
  (void)argc; (void)argv;

  my_class test;
  std::cout << "Class name: " << test.info().class_name() << std::endl
            << "Static class name: " << my_class::static_info().class_name()
            << std::endl;
  std::cout << "Writing 77 into Foo property" << std::endl;
  {
    auto foo_prop = my_class::static_info().properties()[0];
    foo_prop.write<int>(&test, 77);
  }
  {
    auto foo_prop = my_class::static_info().properties()[3];
    foo_prop.write<int>(&test, 88);
  }
  std::cout << "List of properties: " << std::endl;
  for (const auto &p : my_class::static_info().properties()) {
    std::cout << "\t" << p.name() << " => ";
    if (p.is_type_of<std::string>())
      std::cout << p.read<std::string>(&test);
    if (p.is_type_of<int>())
      std::cout << p.read<int>(&test);
    std::cout << std::endl;
  }

  std::cout << "List of methods: " << std::endl;
  for (auto m : my_class::static_info().methods()) {
    std::cout << "\t" << m.name() << "(args:" << m.arg_count() << ")" << " => ";
    if (m.is_const())
      std::cout << "(const) => ";
    if (m.is_type_of<void>())
      m.invoke<void>(&test);
    if (m.is_type_of<bool>())
      std::cout << std::boolalpha << m.invoke<bool>(&test);
    if (m.is_type_of<void, std::string>())
      m.invoke<void, const std::string &>(&test, std::string{"hello world!"});
    std::cout << std::endl;
  }

  return 0;
}
