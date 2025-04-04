cmake_minimum_required(VERSION 3.27 FATAL_ERROR)
project(Project VERSION 1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23) # Project default
set(CMAKE_CXX_STANDARD_REQUIRED On)

add_subdirectory(src)
