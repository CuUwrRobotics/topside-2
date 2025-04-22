file(GLOB HEADER_LIST CONFIGURE_DEPENDS "../include/*.hpp")

add_library(cuuwr_common)

target_sources(cuuwr_common
PUBLIC
    Unimplemented.cpp
)

target_include_directories(cuuwr_common 
PUBLIC 
    ../include
)

target_link_libraries(cuuwr_common
PRIVATE
    spdlog::spdlog
)

target_compile_features(cuuwr_common
PRIVATE
    cxx_std_23
)
