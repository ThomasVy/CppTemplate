set(PROJECT_NAME "app")

find_package(fmt CONFIG REQUIRED)
find_package(cxxopts CONFIG REQUIRED)

add_executable(${PROJECT_NAME} "main.cpp")

# being a cross-platform target, we enforce standards conformance on MSVC
target_compile_options(
    ${PROJECT_NAME}
    PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->"
)

# Link dependencies
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE fmt::fmt-header-only cxxopts::cxxopts
)

target_link_libraries(${PROJECT_NAME} PRIVATE libA)
