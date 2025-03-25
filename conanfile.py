from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout


class MyProjectConan(ConanFile):
    name = "my_project"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    requires = "fmt/11.0.1"
    generators = "CMakeToolchain", "CMakeDeps"

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure(variables={"CMAKE_BUILD_TYPE": str(self.settings.build_type)})
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["fmt"]
