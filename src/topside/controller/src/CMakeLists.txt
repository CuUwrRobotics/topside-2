add_executable(controller)

target_sources(controller
PRIVATE
    main.cpp
    Controller.cpp
    ControllerManager.cpp
)

target_link_libraries(controller
PRIVATE
    spdlog::spdlog
)

target_include_directories(controller 
PRIVATE 
    ../include
)
