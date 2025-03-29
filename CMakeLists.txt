cmake_minimum_required(VERSION 3.27 FATAL_ERROR)
project(Project VERSION 1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23) # Project default
set(CMAKE_CXX_STANDARD_REQUIRED On)

find_package(fmt REQUIRED)
find_package(imgui REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glew REQUIRED)

add_subdirectory(src)
