cmake_minimum_required(VERSION 3.30 FATAL_ERROR)

project(Project LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23) # Project default
set(CMAKE_CXX_STANDARD_REQUIRED On)
include(${CMAKE_SOURCE_DIR}/cmake/Sanitizers.cmake)

include(${CMAKE_SOURCE_DIR}/cmake/CMakeFunctions.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/Formatting.cmake)

add_subdirectory(apps)
add_subdirectory(services)
add_subdirectory(libs)

include(CTest)
include(CPack)
