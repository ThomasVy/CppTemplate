set(PROJECT_NAME "stock_problem")

add_project_library(
    NAME ${PROJECT_NAME}
    SRCS
        src/stock_problem.cpp
    HEADERS
        include/stock_problem/stock_problem.h
)

add_project_test(
    NAME stock_problem_tests
    SRCS
        tests/test_stock_problem.cpp
    PRIVATE_DEPS
        stock_problem
)
