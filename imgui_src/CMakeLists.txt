set(PROJECT_NAME "main")

set(HEADER_FILES)
set(SOURCE_FILES main.cpp)
set(ALL_FILES ${HEADER_FILES} ${SOURCE_FILES})

find_package(fmt CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glew CONFIG REQUIRED)

add_executable(${PROJECT_NAME} ${ALL_FILES})

# being a cross-platform target, we enforce standards conformance on MSVC
target_compile_options(
    ${PROJECT_NAME}
    PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->"
)

# Link dependencies
target_compile_definitions(${PROJECT_NAME} PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLEW)
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE fmt::fmt imgui::imgui glfw GLEW::GLEW
)
