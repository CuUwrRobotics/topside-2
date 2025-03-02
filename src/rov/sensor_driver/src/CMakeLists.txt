add_executable(sensor_driver)

target_sources(sensor_driver
PRIVATE
    sensor_driver.cpp
)

target_link_libraries(sensor_driver
PRIVATE
    cppzmq
    navigator-lib
)

target_include_directories(sensor_driver 
PRIVATE
    ../include
)
