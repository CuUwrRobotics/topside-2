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
enum class InputEventType : std::uint16_t
{
    SYNC   = 0x00, // EV_SYN
    BUTTON = 0x01, // EV_KEY
    STICK  = 0x03, // EV_ABS
};

struct InputEvent
{
    ::timeval     time;
    std::uint16_t type;
    std::uint16_t code;
    std::int32_t  value;
};
} // namespace cuuwr::topside::controller
