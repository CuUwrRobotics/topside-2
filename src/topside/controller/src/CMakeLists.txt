add_executable(controller)

target_sources(controller
PRIVATE
    main.cpp
    controller.cpp
    v_math.cpp
    controls_interpreter.cpp
)

target_link_libraries(controller
PRIVATE
    spdlog::spdlog
)

target_include_directories(controller 
PRIVATE 
    ../include
)
