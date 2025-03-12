/**
 * @file LogitechF310Mappings.hpp
 * @author Cary Keesler
 * @brief
 */

// Standard Library Includes
#include <cstdint>

namespace cuuwr::topside::controller
{
enum class ControllerButtons : std::uint8_t
{
    X              = 0x0,
    A              = 0x1,
    B              = 0x2,
    Y              = 0x3,
    LEFT_BUMPER    = 0x4,
    RIGHT_BUMPER   = 0x5,
    LEFT_TRIGGER   = 0x6,
    RIGHT_TRIGGER  = 0x7,
    BACK           = 0x8,
    START          = 0x9,
    LEFT_JOYSICK   = 0xA,
    RIGHT_JOYSTICK = 0xB,
};

enum class ControllerAxes : std::uint8_t
{
    LEFT_JOYSTICK_X  = 0x0,
    LEFT_JOYSTICK_Y  = 0x1,
    RIGHT_JOYSTICK_X = 0x2,
    RIGHT_JOYSTICK_Y = 0x3,
    D_PAD_X          = 0x4,
    D_PAD_Y          = 0x5,
};
} // namespace cuuwr::topside::controller
