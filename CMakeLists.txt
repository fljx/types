cmake_minimum_required(VERSION 3.11)
project(jx_types VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

add_library(types
    "include/network/ip.h"
    "lib/network/ip.cpp"
)

option(BUILD_TESTING "Build SW tests" OFF)
option(BUILD_DEMO "Build demo app" ON)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

if(BUILD_DEMO)
    add_subdirectory(demo)
endif()
