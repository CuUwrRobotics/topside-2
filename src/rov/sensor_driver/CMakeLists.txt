add_executable(sensor_driver)

target_sources(sensor_driver
PRIVATE
    src/sensor_driver.cpp
)

target_link_libraries(sensor_driver
PRIVATE
    cppzmq
    navigator-lib-obj
)

target_include_directories(sensor_driver 
PRIVATE
    ./include
)
