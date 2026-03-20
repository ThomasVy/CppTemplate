set(PROJECT_NAME "app")

find_package(fmt CONFIG REQUIRED)
find_package(cxxopts CONFIG REQUIRED)

add_project_app(
    NAME ${PROJECT_NAME}
    SRCS
        main.cpp
    PRIVATE_DEPS
        fmt::fmt
        cxxopts::cxxopts
        stock_problem
)
