cmake_minimum_required(VERSION 3.11)
project(topside)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    cppzmq
    GIT_REPOSITORY https://github.com/zeromq/cppzmq
    GIT_TAG        master
)

include(FetchContent)(
    libusb
    GIT_REPOSITORY https://github.com/libusb/libusb
    GIT_TAG        master 
)


add_executable(controller_mapper controller_mapper.h controller_mapper.cpp)
target_link_libraries(controller_mapper
PRIVATE
  cppzmq
)
target_include_directories(controller_mapper PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
