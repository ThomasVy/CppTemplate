set(PROJECT_NAME "app")

find_package(fmt CONFIG REQUIRED)
find_package(cxxopts CONFIG REQUIRED)

add_executable(${PROJECT_NAME} "src/main.cpp")

# being a cross-platform target, we enforce standards conformance on MSVC
target_compile_options(
    ${PROJECT_NAME}
    PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->"
)

# Link dependencies
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE fmt::fmt cxxopts::cxxopts
)

target_link_libraries(${PROJECT_NAME} PRIVATE stock_problem)
target_include_directories(
    ${PROJECT_NAME}
    PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
