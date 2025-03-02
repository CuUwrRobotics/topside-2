include(ExternalProject)

set_directory_properties(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/Rust)
set(RUST_PROJ_DIR "${CMAKE_CURRENT_SOURCE_DIR}/navigator-lib")
set(RUST_OUT_DIR "${RUST_PROJ_DIR}/target/debug")

add_library(navigator-lib
    ${RUST_OUT_DIR}/bindings.h
)

set_target_properties(navigator-lib
PROPERTIES
    LINKER_LANGUAGE CXX
)

target_link_libraries(navigator-lib
PUBLIC
    "${RUST_OUT_DIR}/libbluerobotics_navigator.so"
)

target_include_directories(navigator-lib
PUBLIC
    ${RUST_OUT_DIR}
)
