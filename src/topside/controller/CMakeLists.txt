add_executable(controller)

target_sources(controller
PRIVATE
    src/main.cpp
    src/controller.cpp
    src/v_math.cpp
    src/controls_interpreter.cpp
)

target_link_libraries(controller
PRIVATE
    usb-1.0
)

target_include_directories(controller 
PRIVATE 
    ./include
)
