from conan import ConanFile
from conan.tools.cmake import cmake_layout
from conan.tools.cmake import CMakeToolchain

class CppTemplate(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "VirtualBuildEnv"

    def layout(self):
        cmake_layout(self)

    def configure(self):
         self.options["fmt"].shared = False

    def imports(self):
       tc = CMakeToolchain(self)
       tc.user_presets_path = False # This disables the generation
       tc.generate()
       self.copy("*.dll", "", "bin")
       self.copy("*.dylib", "", "lib")

    def requirements(self):
        self.requires("fmt/11.2.0")
        self.requires("spdlog/1.15.3")
        self.requires("gtest/1.17.0")
        self.requires("cxxopts/3.3.1")
