cmake_minimum_required(VERSION 3.27 FATAL_ERROR)
set(PROJECT_NAME "stock_problem_tests")

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} test_stock_problem.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gtest_main stock_problem)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
