set(PROJECT_NAME "libA")

add_library(${PROJECT_NAME} STATIC "src/libA.cpp")

# being a cross-platform target, we enforce standards conformance on MSVC
target_compile_options(
    ${PROJECT_NAME}
    PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->"
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
