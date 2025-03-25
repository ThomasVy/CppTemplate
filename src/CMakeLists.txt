set(PROJECT_NAME "main")

set(ALL_FILES main.cpp)

add_executable(${PROJECT_NAME} ${ALL_FILES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
