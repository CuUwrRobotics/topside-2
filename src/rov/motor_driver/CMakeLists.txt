add_executable(motor_driver)

target_sources(motor_driver
PRIVATE
    src/motor_driver.cpp
)


target_include_directories(motor_driver 
PRIVATE
    ./include
)

target_link_libraries(motor_driver
PRIVATE
    cppzmq
)
