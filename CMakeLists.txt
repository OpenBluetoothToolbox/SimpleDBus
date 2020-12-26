cmake_minimum_required(VERSION 3.0.0)

SET(PROJECT_DIR_PATH ${CMAKE_CURRENT_SOURCE_DIR})

project(SIMPLEDBUS)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++17 -Wfatal-errors -Wpedantic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -std=c17 -Wfatal-errors -Wpedantic")

# DEPENDENCIES
find_package(PkgConfig REQUIRED)
pkg_search_module(DBUS REQUIRED dbus-1)
if(DBUS_FOUND)
    include_directories(${DBUS_INCLUDE_DIRS})
    message(STATUS "Using DBUS from path: ${DBUS_INCLUDE_DIRS}")
endif()

set(BLE_LIBS ${BLE_LIBS} ${BLUEZ_LIBRARIES} ${DBUS_LIBRARIES} pthread)

# LIBRARY INCLUDES
include_directories(${PROJECT_DIR_PATH}/src-libs)

# OUTPUTS
message("-- [INFO] Building SimpleDBus")
file(GLOB_RECURSE SRC_SIMPLEDBUS_FILES "src-libs/simpledbus/*.cpp")

add_library(simpledbus-static STATIC ${SRC_SIMPLEDBUS_FILES})
add_library(simpledbus SHARED ${SRC_SIMPLEDBUS_FILES})
target_link_libraries(simpledbus-static ${DBUS_LIBRARIES})
target_link_libraries(simpledbus ${DBUS_LIBRARIES})

message("-- [INFO] Building BlueZDBus")
file(GLOB_RECURSE SRC_BLUEZDBUS_FILES "src-libs/bluezdbus/*.cpp")
add_library(bluezdbus-static STATIC ${SRC_BLUEZDBUS_FILES})
add_library(bluezdbus SHARED ${SRC_BLUEZDBUS_FILES})
target_link_libraries(bluezdbus-static simpledbus-static)
target_link_libraries(bluezdbus simpledbus-static)

message("-- [INFO] Building Example")
file(GLOB_RECURSE SRC_EXAMPLE1_FILES "src-example/*.cpp")
add_executable(example ${SRC_EXAMPLE1_FILES})
target_link_libraries(example bluezdbus-static pthread)

message("-- [INFO] Building Example Notification")
file(GLOB_RECURSE SRC_EXAMPLE1_FILES "src-example-minimal/*.cpp")
add_executable(example_minimal ${SRC_EXAMPLE1_FILES})
target_link_libraries(example_minimal bluezdbus-static pthread)
