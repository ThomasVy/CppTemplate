cmake_minimum_required(VERSION 3.27 FATAL_ERROR)
set(PROJECT_NAME "first_test_project")

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} test_something.cpp)
target_link_libraries(${PROJECT_NAME} GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
