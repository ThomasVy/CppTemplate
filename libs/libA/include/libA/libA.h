#pragma once
#include <expected>
#include <iostream>
#include <optional>
#include <string>

namespace libA {

    struct MyClass {
        std::string data;
        MyClass(std::string s) : data(std::move(s)) {
            std::cout << "MyClass constructor: " << data << std::endl;
        }
        MyClass(const MyClass& other) : data(other.data) {
            std::cout << "MyClass copy constructor: " << data << std::endl;
        }
        MyClass(MyClass&& other) noexcept : data(std::move(other.data)) {
            std::cout << "MyClass move constructor: " << data << std::endl;
        }
        ~MyClass() { std::cout << "MyClass destructor: " << data << std::endl; }
    };

    std::expected<MyClass, std::string> create_expected_value(bool success);
    std::optional<MyClass> create_myclass(bool success);
    MyClass create_myclass_normal(bool success);

    void fun();
    void fun2();
    void function();
}  // namespace libA
