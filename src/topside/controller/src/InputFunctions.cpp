/**
 * @file InputFunctions.cpp
 * @author Cary Keesler
 * @brief
 */

// Header Being Defined
#include <controller/InputFunctions.hpp>

#include <spdlog/spdlog.h>

namespace cuuwr::topside::controller
{
namespace ButtonHandlers
{
    auto a(const bool isPressed) -> void
    {
        spdlog::trace("A button {}pressed", (isPressed ? "" : "un"));
    }

    auto b(const bool isPressed) -> void
    {
        spdlog::trace("B button {}pressed", (isPressed ? "" : "un"));
    }

    auto x(const bool isPressed) -> void
    {
        spdlog::trace("X button {}pressed", (isPressed ? "" : "un"));
    }

    auto y(const bool isPressed) -> void
    {
        spdlog::trace("Y button {}pressed", (isPressed ? "" : "un"));
    }

    auto left_bumper(const bool isPressed) -> void
    {
        spdlog::trace("Left bumper {}pressed", (isPressed ? "" : "un"));
    }

    auto right_bumper(const bool isPressed) -> void
    {
        spdlog::trace("Right bumper {}pressed", (isPressed ? "" : "un"));
    }

    auto back(const bool isPressed) -> void
    {
        spdlog::trace("Back button {}pressed", (isPressed ? "" : "un"));
    }

    auto start(const bool isPressed) -> void
    {
        spdlog::trace("Start button {}pressed", (isPressed ? "" : "un"));
    }

    auto logo_button(const bool isPressed) -> void
    {
        spdlog::trace("Logo button {}pressed", (isPressed ? "" : "un"));
    }

    auto left_joystick(const bool isPressed) -> void
    {
        spdlog::trace("Left stick {}pressed", (isPressed ? "" : "un"));
    }

    auto right_joystick(const bool isPressed) -> void
    {
        spdlog::trace("Right stick {}pressed", (isPressed ? "" : "un"));
    }
} // namespace ButtonHandlers

namespace AxisHandlers
{
    auto left_joystick_x(const std::int16_t value) -> void
    {
        spdlog::trace("Left x axis moved");
    }

    auto left_joystick_y(const std::int16_t value) -> void
    {
        spdlog::trace("Left y axis moved");
    }

    auto left_trigger(const std::int16_t value) -> void
    {
        spdlog::trace("Left trigger moved");
    }

    auto right_joystick_x(const std::int16_t value) -> void
    {
        spdlog::trace("Right x axis moved");
    }

    auto right_joystick_y(const std::int16_t value) -> void
    {
        spdlog::trace("Right y axis moved");
    }

    auto right_trigger(const std::int16_t value) -> void
    {
        spdlog::trace("Right trigger moved");
    }

    auto d_pad_x(const std::int16_t value) -> void
    {
        spdlog::trace("D-pad x moved");
    }

    auto d_pad_y(const std::int16_t value) -> void
    {
        spdlog::trace("D-pad y moved");
    }
} // namespace AxisHandlers
} // namespace cuuwr::topside::controller
