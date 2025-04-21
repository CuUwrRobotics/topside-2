/**
 * @file Joystick.hpp
 * @author Cary Keesler
 * @brief
 */

// System Includes
#include <sys/time.h>

// Standard Library Includes
#include <cstdint>

namespace cuuwr::topside::controller
{
enum class JoystickEventType : std::uint8_t
{
    BUTTON      = 0x01,
    AXIS        = 0x02,
    INIT        = 0x80,
    BUTTON_INIT = BUTTON | INIT,
    AXIS_INIT   = BUTTON | AXIS,
};

struct JoystickEvent
{
    std::uint32_t  timestamp; // In milliseconds. Since what? idk
    std::int16_t   value;
    JoystickEventType eventType;
    std::uint8_t   id;
};
} // namespace cuuwr::topside::controller
