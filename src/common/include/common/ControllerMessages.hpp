/**
 * @file ControllerMessages.hpp
 * @author Cary Keesler
 * @brief
 */

// Standard Library Includes
#include <cstdint>

namespace cuuwr::common::controller_messages
{
enum class ControlLoop : std::uint8_t
{
};

enum class CameraControl : std::uint8_t
{
    NEXT_CAMERA,
    PREVIOUS_CAMERA,
};

enum class MotorDriver : std::uint8_t
{
    ARM_MOTORS,
    DISARM_MOTORS,
    OPEN_CLAW,
    CLOSE_CLAW,
};
} // namespace cuuwr::common::controller_messages
