cmake_minimum_required(VERSION 3.0.0)

project(SIMPLEDBUS_EXAMPLES)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++17 -Wfatal-errors -Wpedantic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -std=c17 -Wfatal-errors -Wpedantic")

# Include simpledbus and bluezdbus
# Build artifacts in a separate folder
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/.. ${CMAKE_BINARY_DIR}/simpledbus)
include_directories(${SIMPLEDBUS_INCLUDES})

add_subdirectory(ble_nus)
add_subdirectory(manuf_data)
add_subdirectory(notification)
