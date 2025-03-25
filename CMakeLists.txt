cmake_minimum_required(VERSION 3.27 FATAL_ERROR)
project(
  Project
  VERSION 1.0
  LANGUAGES CXX
)

find_package(fmt REQUIRED)

add_subdirectory(src)
