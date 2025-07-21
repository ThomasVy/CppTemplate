cmake_minimum_required(VERSION 3.27 FATAL_ERROR)
project(Project VERSION 1.0 LANGUAGES CXX)
include(CTest)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23) # Project default
set(CMAKE_CXX_STANDARD_REQUIRED On)
enable_testing()

add_subdirectory(apps/app)
add_subdirectory(external/common)
add_subdirectory(libs/libA)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
