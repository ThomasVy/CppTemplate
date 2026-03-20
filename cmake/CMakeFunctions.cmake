function(add_project_library)
  cmake_parse_arguments(
    LIB
    ""                                              # Options
    "NAME"                                          # Single-value args
    "SRCS;HEADERS;PUBLIC_DEPS;PRIVATE_DEPS;COMPILE_OPTIONS"  # Multi-value args
    ${ARGN}
  )

  if(NOT LIB_NAME)
    message(FATAL_ERROR "add_project_library: NAME is required")
  endif()

  list(LENGTH LIB_SRCS _src_count)

  if(_src_count EQUAL 0)
    # Header-only: INTERFACE library
    add_library(${LIB_NAME} INTERFACE)
    target_include_directories(${LIB_NAME}
      INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    )
    if(LIB_PUBLIC_DEPS)
      target_link_libraries(${LIB_NAME} INTERFACE ${LIB_PUBLIC_DEPS})
    endif()
  else()
    add_library(${LIB_NAME} STATIC ${LIB_SRCS} ${LIB_HEADERS})
    target_include_directories(${LIB_NAME}
      PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    )
    if(LIB_PUBLIC_DEPS)
      target_link_libraries(${LIB_NAME} PUBLIC ${LIB_PUBLIC_DEPS})
    endif()
    if(LIB_PRIVATE_DEPS)
      target_link_libraries(${LIB_NAME} PRIVATE ${LIB_PRIVATE_DEPS})
    endif()
    if(LIB_COMPILE_OPTIONS)
      target_compile_options(${LIB_NAME} PRIVATE ${LIB_COMPILE_OPTIONS})
    endif()
  endif()

  set_property(DIRECTORY PROPERTY PROJECT_LIBRARY_TARGET ${LIB_NAME})
endfunction()

function(add_project_app)
  cmake_parse_arguments(
    APP
    ""                                              # Options
    "NAME"                                          # Single-value args
    "SRCS;HEADERS;PRIVATE_DEPS;COMPILE_OPTIONS;COMPILE_DEFINITIONS"  # Multi-value args
    ${ARGN}
  )

  if(NOT APP_NAME)
    message(FATAL_ERROR "add_project_app: NAME is required")
  endif()

  list(LENGTH APP_SRCS _src_count)
  if(_src_count EQUAL 0)
    message(FATAL_ERROR "add_project_app: SRCS is required")
  endif()

  add_executable(${APP_NAME} ${APP_SRCS} ${APP_HEADERS})

  # no src or include folder for app, so include current dir to find headers
  target_include_directories(${APP_NAME}
    PRIVATE
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  )

  if(APP_PRIVATE_DEPS)
    target_link_libraries(${APP_NAME} PRIVATE ${APP_PRIVATE_DEPS})
  endif()
  if(APP_COMPILE_OPTIONS)
    target_compile_options(${APP_NAME} PRIVATE ${APP_COMPILE_OPTIONS})
  endif()
  if(APP_COMPILE_DEFINITIONS)
    target_compile_definitions(${APP_NAME} PRIVATE ${APP_COMPILE_DEFINITIONS})
  endif()

  install(TARGETS ${APP_NAME} DESTINATION bin)
endfunction()

function(add_project_test)
  cmake_parse_arguments(
    TEST
    ""                                       # Options
    "NAME"                        # Single-value args
    "SRCS;HEADERS;PRIVATE_DEPS;COMPILE_OPTIONS;COMPILE_DEFINITIONS;INCLUDE_DIRS"  # Multi-value args
    ${ARGN}
  )

  if(NOT BUILD_TESTING)
    return()
  endif()

  if(NOT TEST_NAME)
    message(FATAL_ERROR "add_project_test: NAME is required")
  endif()

  list(LENGTH TEST_SRCS _src_count)
  if(_src_count EQUAL 0)
    message(FATAL_ERROR "add_project_test: SRCS is required")
  endif()

  add_executable(${TEST_NAME} ${TEST_SRCS} ${TEST_HEADERS})

  target_include_directories(${TEST_NAME}
    PRIVATE
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/test>
      ${TEST_INCLUDE_DIRS}
  )

  get_directory_property(_project_library_target PROPERTY PROJECT_LIBRARY_TARGET)
  if(_project_library_target)
    target_link_libraries(${TEST_NAME} PRIVATE ${_project_library_target})
  endif()

  if(TEST_PRIVATE_DEPS)
    target_link_libraries(${TEST_NAME} PRIVATE ${TEST_PRIVATE_DEPS})
  endif()

  find_package(GTest REQUIRED)
  target_link_libraries(${TEST_NAME} PRIVATE GTest::gtest_main)

  if(TEST_COMPILE_OPTIONS)
    target_compile_options(${TEST_NAME} PRIVATE ${TEST_COMPILE_OPTIONS})
  endif()
  if(TEST_COMPILE_DEFINITIONS)
    target_compile_definitions(${TEST_NAME} PRIVATE ${TEST_COMPILE_DEFINITIONS})
  endif()

  include(GoogleTest)
  gtest_discover_tests(${TEST_NAME})
  
endfunction()