add_executable(control_loop)

target_sources(control_loop
PRIVATE
    src/main.c
    src/pid.c
)

target_include_directories(control_loop
PRIVATE
    ./include
)
