// Standard Library Includes
#include <cstdlib>

// Third Party Includes
#include <spdlog/cfg/env.h>

// Project Includes
#include <controller/Controller.hpp>

auto main() -> int
{
    spdlog::cfg::load_env_levels();

    cuuwr::topside::controller::Controller controllerManager;

    controllerManager.dump_inputs_to_terminal();

    return EXIT_SUCCESS;
}
