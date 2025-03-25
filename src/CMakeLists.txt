set(PROJECT_NAME "main")

set(HEADER_FILES)
set(SOURCE_FILES main.cpp)
set(ALL_FILES ${HEADER_FILES} ${SOURCE_FILES})

add_executable(${PROJECT_NAME} ${ALL_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)

# being a cross-platform target, we enforce standards conformance on MSVC
target_compile_options(${PROJECT_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->")

# Link dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
