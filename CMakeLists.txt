cmake_minimum_required(VERSION 3.27 FATAL_ERROR)
project(Project VERSION 1.0 LANGUAGES CXX)
include(CTest)
set(CMAKE_CXX_STANDARD 23) # Project default
set(CMAKE_CXX_STANDARD_REQUIRED On)

include(${CMAKE_SOURCE_DIR}/cmake/CMakeFunctions.cmake)

add_subdirectory(apps)
add_subdirectory(services)
add_subdirectory(libs)

include(CPack)
