add_subdirectory(controller)

add_custom_target(topside)

add_dependencies(topside
    controller
)
