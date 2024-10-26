cmake_minimum_required(VERSION 3.11)
project(sensor_driver)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    cppzmq
    GIT_REPOSITORY https://github.com/zeromq/cppzmq.git
    GIT_TAG        master
)

FetchContent_MakeAvailable(cppzmq)

add_executable(sensor_driver sensor_driver.cpp)
target_link_libraries(sensor_driver
PRIVATE
  cppzmq
)
target_include_directories(sensor_driver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
