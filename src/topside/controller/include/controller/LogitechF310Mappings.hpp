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
 * @brief Button mappings determined through testing. Mappings provided by
 * <linux/input-event-codes.h> are incorrect for this controller
 *
 */
enum class ControllerButton : std::uint16_t
{
    X              = 0x120,
    A              = 0x121,
    B              = 0x122,
    Y              = 0x123,
    LEFT_BUMPER    = 0x124,
    RIGHT_BUMPER   = 0x125,
    LEFT_TRIGGER   = 0x126,
    RIGHT_TRIGGER  = 0x127,
    BACK           = 0x128,
    START          = 0x129,
    LEFT_JOYSTICK  = 0x12A,
    RIGHT_JOYSTICK = 0x12B,
};

enum class ControllerAxis : std::uint16_t
{
    LEFT_JOYSTICK_X  = 0x0,
    LEFT_JOYSTICK_Y  = 0x1,
    RIGHT_JOYSTICK_X = 0x2,
    RIGHT_JOYSTICK_Y = 0x5,
    D_PAD_X          = 0x16,
    D_PAD_Y          = 0x17,
};

enum class AxisExtrema : std::int32_t
{
    JOYSTICK_UP    = 0,
    JOYSTICK_DOWN  = 255,
    JOYSTICK_LEFT  = 0,
    JOYSTICK_RIGHT = 255,
    DPAD_UP        = -1,
    DPAD_DOWN      = 1,
    DPAD_LEFT      = -1,
    DPAD_RIGHT     = 1,
};
} // namespace cuuwr::topside::controller
