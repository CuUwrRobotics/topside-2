file(GLOB HEADER_LIST CONFIGURE_DEPENDS "../include/*.hpp")

add_executable(controller)

target_sources(controller
PRIVATE
    main.cpp
    Controller.cpp
    ControllerManager.cpp
    ${HEADER_LIST}
)

target_link_libraries(controller
PRIVATE
    spdlog::spdlog
)

target_include_directories(controller 
PRIVATE 
    ../include
)

target_compile_features(controller
PRIVATE
    cxx_std_23
)
