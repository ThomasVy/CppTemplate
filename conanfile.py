from conan import ConanFile
from conan.tools.cmake import cmake_layout

class CppTemplate(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"

    def layout(self):
        cmake_layout(self)

    def requirements(self):
        self.requires("fmt/11.2.0")
        self.requires("spdlog/1.15.3")
        self.requires("gtest/1.17.0")
        self.requires("cxxopts/3.3.1")
