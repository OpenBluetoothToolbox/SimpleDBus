cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(SIMPLEDBUS)

# Load dependencies
find_package(PkgConfig REQUIRED)
pkg_search_module(DBUS REQUIRED dbus-1)

# Detect if the project is being build within a project or standalone.
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(STANDALONE true)

    # Configure the build path
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
else()
    set(STANDALONE false)
endif()

# Library includes
include_directories(${DBUS_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# OUTPUTS
message("-- [INFO] Building SimpleDBus")
file(GLOB_RECURSE SRC_SIMPLEDBUS_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(simpledbus-static STATIC ${SRC_SIMPLEDBUS_FILES})
add_library(simpledbus SHARED ${SRC_SIMPLEDBUS_FILES})

target_compile_options(simpledbus-static PRIVATE -std=c++17 -fPIC -Wfatal-errors -Wpedantic -O3)
target_compile_options(simpledbus PRIVATE -std=c++17 -fPIC -Wfatal-errors -Wpedantic -O3)

target_link_libraries(simpledbus-static PUBLIC ${DBUS_LIBRARIES})
target_link_libraries(simpledbus PUBLIC ${DBUS_LIBRARIES})

# Export the variables needed by the parent project
if(NOT ${STANDALONE})
    set(SIMPLEDBUS_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src ${DBUS_INCLUDE_DIRS} PARENT_SCOPE)
endif()
