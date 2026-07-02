from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, cmake_layout


class CppTemplate(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeConfigDeps", "CMakeDeps", "VirtualBuildEnv"

    def layout(self):
        cmake_layout(self)

    def configure(self):
        self.options["fmt"].shared = False
        self.options["boost"].header_only = True
        self.options["boost"].without_python = True
        self.options["boost"].without_test = True

    def imports(self):
        tc = CMakeToolchain(self)
        tc.user_presets_path = False  # This disables the generation
        tc.generate()
        self.copy("*.dll", "", "bin")
        self.copy("*.dylib", "", "lib")

    def requirements(self):
        self.requires("fmt/12.1.0")
        self.requires("spdlog/1.17.0")
        self.requires("gtest/1.17.0")
        self.requires("cxxopts/3.3.1")
        self.requires("openssl/4.0.1")
        self.requires("boost/1.91.0")
        self.requires("magic_enum/0.9.7")
        self.requires("nlohmann_json/3.12.0")
