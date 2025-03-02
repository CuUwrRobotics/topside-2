cmake_minimum_required(VERSION 3.20...3.30)

set(CPPZMQ_BUILD_TESTS OFF CACHE INTERNAL "")

project(underwater_robotics
    VERSION 0.1.0
    DESCRIPTION "Topside and ROV software"
)

include(cmake/fetch_deps.cmake)

add_subdirectory(src)
add_subdirectory(lib)
