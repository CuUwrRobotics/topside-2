/**
 * @file Controller.hpp
 * @author Cary Keesler
 * @brief
 */

#pragma once

// Standard Library Includes
#include <variant>

// Project Includes
#include <controller/LogitechF310Mappings.hpp>

namespace cuuwr::topside::controller
{
struct AxisInput
{
    ControllerAxis axis;
    std::int16_t   position;
};

struct ButtonInput
{
    ControllerButton button;
    bool             isPressed;
};

using ControllerInput = std::variant<AxisInput, ButtonInput>;
} // namespace cuuwr::topside::controller
