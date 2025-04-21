/**
 * @file LogitechF310Mappings.hpp
 * @author Cary Keesler
 * @brief
 */

// Standard Library Includes
#include <cstdint>

namespace cuuwr::topside::controller
{
/**
 * @brief Button mappings determined through testing.
 */
enum class ControllerButton : std::uint8_t
{
    A              = 0x0,
    B              = 0x1,
    X              = 0x2,
    Y              = 0x3,
    LEFT_BUMPER    = 0x4,
    RIGHT_BUMPER   = 0x5,
    BACK           = 0x6,
    START          = 0x7,
    LOGO_BUTTON    = 0x8,
    LEFT_JOYSTICK  = 0x9,
    RIGHT_JOYSTICK = 0x10,
};

enum class ControllerAxis : std::uint8_t
{
    LEFT_JOYSTICK_X  = 0x0,
    LEFT_JOYSTICK_Y  = 0x1,
    LEFT_TRIGGER     = 0x2,
    RIGHT_JOYSTICK_X = 0x3,
    RIGHT_JOYSTICK_Y = 0x4,
    RIGHT_TRIGGER    = 0x5,
    D_PAD_X          = 0x6,
    D_PAD_Y          = 0x7,
};

enum class AxisExtrema : std::int16_t
{
    JOYSTICK_UP       = -32'767,
    JOYSTICK_DOWN     = 32'767,
    JOYSTICK_LEFT     = -32'767,
    JOYSTICK_RIGHT    = 32'767,
    TRIGGER_UNPRESSED = -32'767,
    TRIGGER_PRESSED   = 32'767,
    DPAD_UP           = -32'767,
    DPAD_DOWN         = 32'767,
    DPAD_LEFT         = -32'767,
    DPAD_RIGHT        = 32'767,
};
} // namespace cuuwr::topside::controller
