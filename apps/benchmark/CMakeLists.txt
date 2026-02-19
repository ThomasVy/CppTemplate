set(PROJECT_NAME "benchmark")

find_package(benchmark REQUIRED)
# ...
add_executable(${PROJECT_NAME} "src/main.cpp")

target_link_libraries(${PROJECT_NAME} benchmark::benchmark_main)
