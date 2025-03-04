add_subdirectory(control_loop)
add_subdirectory(motor_driver)
add_subdirectory(sensor_driver)

add_custom_target(rov)

add_dependencies(rov
    control_loop
    motor_driver
    sensor_driver
)
