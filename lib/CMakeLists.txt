include(ExternalProject)

set_directory_properties(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/Rust)
set(RUST_PROJ_DIR "${CMAKE_CURRENT_SOURCE_DIR}/navigator-lib")
set(RUST_OUT_DIR "${RUST_PROJ_DIR}/target/debug")

add_custom_target(navigator-lib
    COMMAND cd ${RUST_PROJ_DIR} && cargo build
    COMMENT "C binds generated: ${RUST_OUT_DIR}"
)

add_library(navigator-lib-obj
    ${RUST_OUT_DIR}/bindings.h
)

set_target_properties(navigator-lib-obj
PROPERTIES
LINKER_LANGUAGE CXX
)

add_dependencies(navigator-lib-obj
    navigator-lib
)

target_link_libraries(navigator-lib-obj
PUBLIC
    "${RUST_OUT_DIR}/libbluerobotics_navigator.so"
)

target_include_directories(navigator-lib-obj
PUBLIC
    ${RUST_OUT_DIR}
)
