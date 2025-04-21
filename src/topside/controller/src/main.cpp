// Standard Library Includes
#include <cstdlib>

// Third Party Includes
#include <spdlog/cfg/env.h>

// Project Includes
#include <controller/ControllerManager.hpp>

auto main() -> int
{
    spdlog::cfg::load_env_levels();

    cuuwr::topside::controller::ControllerManager controllerManager;

    controllerManager.run();

    return EXIT_SUCCESS;
}
