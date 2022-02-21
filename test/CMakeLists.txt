cmake_minimum_required(VERSION 3.16)
project(simpledbus_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

if(CMAKE_COVERAGE MATCHES "On")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
endif() # CMAKE_COVERAGE MATCHES "On"

# Include SimpleDBus
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/.. ${CMAKE_BINARY_DIR}/simpledbus)
include_directories(${SIMPLEDBUS_INCLUDES})

find_package(Python3 COMPONENTS Development REQUIRED)

enable_testing()
find_package(GTest REQUIRED)

set(
  SRC_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/test_callback.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/test_holder.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/test_message.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/test_proxy_interfaces.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/test_proxy_children.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/test_path.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/helpers/PythonRunner.cpp
)

add_executable(simpledbus_test ${SRC_FILES})
target_link_libraries(simpledbus_test simpledbus-static ${GTEST_LIBRARIES} ${Python3_LIBRARIES} pthread)
target_include_directories(simpledbus_test PRIVATE ${GTEST_INCLUDE_DIRS} ${Python3_INCLUDE_DIRS})

add_custom_command (TARGET simpledbus_test POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/python/ ${CMAKE_BINARY_DIR}
)

if(CMAKE_COVERAGE MATCHES "On")
  find_program(GCOVR_PATH gcovr)
  if(NOT GCOVR_PATH)
    message(FATAL_ERROR "gcovr not found! Aborting...")
  endif() # NOT GCOVR_PATH
  # Create the gcov target. Run coverage tests with 'make gcov'
  add_custom_target(gcov
    COMMAND GTEST_OUTPUT=xml:results/ GTEST_COLOR=1 ctest -V
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  )
  add_custom_command(TARGET gcov
    # cli report for local testing
    COMMAND echo "Generating cli coverage report"
    COMMAND gcovr -r .. . -e ${CMAKE_BINARY_DIR}/_deps -e ${CMAKE_CURRENT_LIST_DIR}/..
    # xml report for ci
    COMMAND echo "Generating xml coverage report"
    COMMAND gcovr --xml -r .. . -e ${CMAKE_BINARY_DIR}/_deps -e ${CMAKE_CURRENT_LIST_DIR}/.. -o cov.xml
  )
  add_dependencies(gcov simpledbus_test)
  add_test(output_test ${CMAKE_BINARY_DIR}/simpledbus_test)
endif() # CMAKE_BUILD_TYPE MATCHES "Coverage" 