/**
 * @file Controller.cpp
 * @author Cary Keesler
 * @brief
 */

// Header Being Defined
#include <controller/Controller.hpp>

// System Includes
#include <fcntl.h>
#include <unistd.h>

// Standard Library Includes
#include <cstdlib>
#include <filesystem>
#include <optional>
#include <regex>

// Third Party Includes
#include <spdlog/spdlog.h>

namespace cuuwr::topside::controller
{
Controller::Controller()
{
    const auto inputDirectory = std::filesystem::absolute("/dev/input");
    const auto joystickRegex  = std::regex("/dev/input/js[0-9]");

    // I've been told that this is cursed ¯\_(ツ)_/¯
    // Initializes variable using an immediately invoked lambda expression
    const auto maybeJoystickFile = [&]() -> std::optional<std::filesystem::path>
    {
        spdlog::debug("Looking for attached controllers");

        // Looks through all items in the /dev/input directory for a file named
        // js followed by a number (i.e. js0) using the regex defined above
        for (const auto file :
             std::filesystem::directory_iterator(inputDirectory))
        {
            spdlog::trace("Checking file ({}) against regex",
                          file.path().string());

            if (std::regex_match(file.path().string(), joystickRegex))
            {
                return file.path();
            }
        }

        // Returns nullopt to indicate that a controller wasn't found
        return std::nullopt;
    }();

    // If nullopt was returned, has_value() is false
    if (!maybeJoystickFile.has_value())
    {
        spdlog::error("No controllers are connected!");
        std::exit(EXIT_FAILURE);
    }

    const auto& joystickFile = maybeJoystickFile.value();
    spdlog::info("Found controller at {}", joystickFile.c_str());

    spdlog::debug("Attempting to aquire handle to controller!");
    m_ControllerFileDescriptor
        = ::open(joystickFile.c_str(), O_RDONLY | O_NONBLOCK);

    if (m_ControllerFileDescriptor == -1)
    {
        spdlog::error("Failed to aquire handle to controller!");
        std::exit(EXIT_FAILURE);
    }

    spdlog::info("Successfully acquired handle to controller!");
}

Controller::~Controller()
{
    ::close(m_ControllerFileDescriptor);
}
} // namespace cuuwr::topside::controller

