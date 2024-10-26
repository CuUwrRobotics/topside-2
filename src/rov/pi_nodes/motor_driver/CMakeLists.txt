cmake_minimum_required(VERSION 3.11)
project(motor_driver)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    cppzmq
    GIT_REPOSITORY https://github.com/zeromq/cppzmq
    GIT_TAG        master
)

add_executable(motor_driver motor_driver.h motor_driver.cpp)
target_link_libraries(motor_driver
PRIVATE
  cppzmq
)
target_include_directories(motor_driver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
