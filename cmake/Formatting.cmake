find_program(CLANG_FORMAT_EXE NAMES clang-format)
find_program(CLANG_TIDY_EXE NAMES clang-tidy)

file(GLOB_RECURSE ALL_PROJECT_SOURCES
    ${CMAKE_SOURCE_DIR}/apps/*.cpp
    ${CMAKE_SOURCE_DIR}/apps/*.hpp
    ${CMAKE_SOURCE_DIR}/apps/*.h
    ${CMAKE_SOURCE_DIR}/services/*.cpp
    ${CMAKE_SOURCE_DIR}/services/*.hpp
    ${CMAKE_SOURCE_DIR}/services/*.h
    ${CMAKE_SOURCE_DIR}/libs/*.cpp
    ${CMAKE_SOURCE_DIR}/libs/*.hpp
    ${CMAKE_SOURCE_DIR}/libs/*.h
)

# clang-tidy is meant to run on translation units; headers are checked transitively
# through the .clang-tidy HeaderFilterRegex when included by source files.
file(GLOB_RECURSE ALL_PROJECT_TU_SOURCES
    ${CMAKE_SOURCE_DIR}/apps/*.cpp
    ${CMAKE_SOURCE_DIR}/apps/*.c
    ${CMAKE_SOURCE_DIR}/services/*.cpp
    ${CMAKE_SOURCE_DIR}/services/*.c
    ${CMAKE_SOURCE_DIR}/libs/*.cpp
    ${CMAKE_SOURCE_DIR}/libs/*.c
)

if(CLANG_FORMAT_EXE)
    add_custom_target(format
        COMMAND ${CLANG_FORMAT_EXE} -i ${ALL_PROJECT_SOURCES}
        COMMENT "Running clang-format on project sources"
    )
else()
    message(STATUS "clang-format not found; 'format' target disabled")
endif()

if(CLANG_TIDY_EXE)
    add_custom_target(clang-tidy
        COMMAND ${CLANG_TIDY_EXE} -p ${CMAKE_BINARY_DIR} ${ALL_PROJECT_TU_SOURCES}
        COMMENT "Running clang-tidy on project source files"
    )
else()
    message(STATUS "clang-tidy not found; 'clang-tidy' target disabled")
endif()

add_custom_target(install-hooks
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_SOURCE_DIR} git config core.hooksPath scripts
    COMMENT "Installing git hooks from scripts/"
)
