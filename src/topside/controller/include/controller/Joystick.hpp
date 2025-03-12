/**
 * @file Joystick.hpp
 * @author Cary Keesler
 * @brief
 */

// Standard Library Includes
#include <cstdint>

namespace cuuwr::topside::controller
{
enum class JoystickEventType : std::uint8_t
{
    BUTTON = 0x01,
    AXIS   = 0x02,
    INIT   = 0x80,
};

struct JoystickEvent
{
    std::uint32_t     time;
    std::int16_t      value;    /* value */
    JoystickEventType type;     /* event type */
    std::uint8_t      buttonID; /* axis/button number */
};
} // namespace cuuwr::topside::controller
