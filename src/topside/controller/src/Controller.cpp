/**
 * @file Controller.cpp
 * @author Cary Keesler
 * @brief
 */

// Header Being Defined
#include <controller/Controller.hpp>

// System Includes
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>

// Standard Library Includes
#include <array>
#include <cstdlib>
#include <filesystem>
#include <optional>
#include <string_view>

// Third Party Includes
#include <spdlog/spdlog.h>

namespace cuuwr::topside::controller
{
Controller::Controller()
{
    const auto inputByID = std::filesystem::absolute("/dev/input/by-id");

    //! For the current purposes, embedding the device IDs in the executable
    //! works since we aren't going to be using a controller other than the two
    //! we have. However, we may end up getting a new controller at some point
    //! and when we do this will no longer work. It might be worth creating a
    //! config file of sorts that the controller ID can be loaded from at
    //! runtime.
    using namespace std::string_view_literals;
    constexpr std::array<std::string_view, 2> CONTROLLER_IDS
        = { "usb-Logitech_Logitech_Dual_Action_9AA95248-event-joystick"sv,
            "usb-Logitech_Logitech_Dual_Action_F240D0A4-event-joystick"sv };

    // I've been told that this is cursed ¯\_(ツ)_/¯
    // Initializes variable using an immediately invoked lambda expression
    const auto maybeControllerPath
        = [&]() -> std::optional<std::filesystem::path>
    {
        spdlog::debug("Looking for attached controllers with known IDs");

        // Use controller IDs to get around having to identify each event* file
        // in /dev/input. The by-id directory contains symlinks for attached
        // devices that point to the correct event file
        for (const auto currentID : CONTROLLER_IDS)
        {
            spdlog::trace("Checking controller ID: {}", currentID);

            if (std::filesystem::exists(inputByID / currentID))
            {
                return inputByID / currentID;
            }
        }

        // Returns nullopt to indicate that a controller wasn't found
        return std::nullopt;
    }();

    // If nullopt was returned, has_value() is false
    if (!maybeControllerPath.has_value())
    {
        spdlog::error("No known controllers are connected!");
        std::exit(EXIT_FAILURE);
    }

    const auto& joystickFile = maybeControllerPath.value();
    spdlog::info("Found controller with known ID: {}",
                 joystickFile.filename().generic_string());

    spdlog::debug("Attempting to aquire handle to controller");
    m_ControllerFileDescriptor
        = ::open(joystickFile.c_str(), O_RDONLY | O_NONBLOCK);

    // ::open experienced an error
    if (m_ControllerFileDescriptor == -1)
    {
        spdlog::error("Failed to aquire handle to controller!");
        std::exit(EXIT_FAILURE);
    }

    spdlog::info("Successfully acquired handle to controller!");
}

auto Controller::report_inputs() -> void
{
    ::input_event inputEvent;

    while (::read(m_ControllerFileDescriptor, &inputEvent, sizeof(inputEvent)))
    {
        spdlog::info(R"({{"type": {}, "code": {}, "value": {}}})",
                     inputEvent.type,
                     inputEvent.code,
                     inputEvent.value);
    }
}

Controller::~Controller()
{
    spdlog::info("Freeing handle to controller");
    ::close(m_ControllerFileDescriptor);

    //! Currently not handling possible errors with ::close. Error handling is
    //! likely not ever going to be needed because the controller object should
    //! only ever be destroyed when the program is almost finished running and
    //! the handle will be reclaimed by the OS automatically anyway
}
} // namespace cuuwr::topside::controller

