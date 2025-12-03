#include "libA/libA.h"

#include <iostream>

namespace libA {
    void function() { std::cout << "hello world" << std::endl; }
    void fun() { std::cout << "We are inside fun" << std::endl; }
    void fun2() { std::cout << "libA::fun2()" << std::endl; }

    // Lesson learned: do not use both nrvo and rvo in the same function
    std::expected<MyClass, std::string> create_expected_value(bool success) {
        if (success) {
            return std::expected<MyClass, std::string>(
                std::in_place, "MyClass Data");
        }
        return std::unexpected("Error occurred");
    }
    std::optional<MyClass> create_myclass(bool success) {
        if (success) {
            return std::make_optional<MyClass>("Optional MyClass Data");
        }
        return std::nullopt;
    }

    MyClass create_myclass_normal(bool success) {
        if (success) {
            MyClass obj("Temporary MyClass Data");
            return obj;
        }
        return MyClass("Default MyClass Data");
    }
}  // namespace libA
