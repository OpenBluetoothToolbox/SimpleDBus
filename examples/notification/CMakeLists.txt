cmake_minimum_required(VERSION 3.16.0)

project(EXAMPLE_NOTIFICATION)

if (CONAN_BUILD)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
endif()

message("-- [INFO] Building Example")
add_executable(example_notification main.cpp)
if (CONAN_BUILD)
    target_include_directories(example_notification PUBLIC ${CONAN_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include)
    target_link_libraries(example_notification ${CONAN_LIBS} simpledbus-static)
else()
    target_link_libraries(example_notification simpledbus-static)
endif()
