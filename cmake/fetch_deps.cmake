include(FetchContent)

FetchContent_Declare(spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog
    GIT_TAG v1.15.1
)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(cppzmq
    GIT_REPOSITORY https://github.com/zeromq/cppzmq
    GIT_TAG v4.10.0
)
FetchContent_MakeAvailable(cppzmq)
