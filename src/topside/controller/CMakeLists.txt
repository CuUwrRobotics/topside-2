cmake_minimum_required(VERSION 3.11)
project(topside)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add_subdirectory(controller)

# Set the pkg-config path for libusb
set(PKG_CONFIG_PATH "/opt/homebrew/Cellar/libusb/1.0.27/lib/pkgconfig")

# Use pkg-config to find libusb
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBUSB REQUIRED libusb-1.0)

# Include libusb headers
include_directories(${LIBUSB_INCLUDE_DIRS})
include_directories("/opt/homebrew/Cellar/libusb/1.0.27/include")

# Add the directory containing libusb-1.0 library
link_directories("/opt/homebrew/Cellar/libusb/1.0.27/lib")

# Add the executable
add_executable(controller 
            main.cpp
            controller.h 
            controller.cpp
            v_math.h 
            v_math.cpp 
            controls_interpreter.h
            controls_interpreter.cpp
        )


# Link to the found libusb library
target_link_libraries(controller PRIVATE ${LIBUSB_LIBRARIES})

# Include the current directory for header files
target_include_directories(controller PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
