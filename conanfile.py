import os
from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout
from conan.tools.files import copy


class MyProjectConan(ConanFile):
    name = "my_project"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        # Runtime requirements
        self.requires("fmt/11.0.1")
        # self.requires("imgui/1.91.8-docking")
        # self.requires("glfw/3.4")
        # self.requires("glew/2.2.0")

    # def generate(self):
    #     copy(self, "*glfw*", os.path.join(self.dependencies["imgui"].package_folder,
    #          "res", "bindings"), os.path.join(self.source_folder, "src/bindings"))
    #     copy(self, "*opengl3*", os.path.join(self.dependencies["imgui"].package_folder,
    #          "res", "bindings"), os.path.join(self.source_folder, "src/bindings"))

    def build_requirements(self):
        # Build requirements
        self.tool_requires("cmake/[>=3.27]")
        self.tool_requires("ninja/1.11.1")

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure(variables={"CMAKE_BUILD_TYPE": str(self.settings.build_type)})
        cmake.build()

