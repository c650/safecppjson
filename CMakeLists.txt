cmake_minimum_required(VERSION 3.16)
project(safecppjson LANGUAGES CXX VERSION 0.0.2)

set(CMAKE_GENERATOR "Ninja")

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS --std=c++20)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

macro(find_package_and_export)
    find_package(${ARGN})

    string(REPLACE ";" " " argn_with_spaces "${ARGN}")
    string(APPEND ${PROJECT_NAME}_FIND_DEPENDENCY_CALLS
        "find_dependency("
        "${argn_with_spaces}"
        ")\n"
    )
endmacro()

find_package_and_export(cpprestsdk REQUIRED)
find_package_and_export(fmt REQUIRED)

# file(GLOB_RECURSE SOURCES "src/*.cpp")
# file (GLOB_RECURSE HEADERS "src/*.hpp")

add_library(${PROJECT_NAME} INTERFACE)
target_compile_definitions(
    ${PROJECT_NAME}
    INTERFACE
)
target_include_directories(
  ${PROJECT_NAME}
  INTERFACE $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/src>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_link_libraries(safecppjson INTERFACE cpprestsdk::cpprest fmt::fmt)

add_subdirectory(tests/)

# do install stuff.
# https://here-be-braces.com/installing-and-exporting-cmake-projects/
include("cmake/setup_installation.cmake")
