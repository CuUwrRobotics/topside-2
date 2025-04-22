/**
 * @file SocketPortNumbers.hpp
 * @author Cary Keesler
 * @brief
 */

// Standard Library Includes
#include <cstdint>
#include <string>

namespace cuuwr::common
{
namespace socket_ports
{
    constexpr std::uint16_t CONTROLLER_PUBLISHER = 5'000;
} // namespace socket_ports

namespace socket_topics
{
    const std::string CAMERA_CONTROL_TOPIC = "camera_control";
    const std::string MOTOR_DRIVER_TOPIC   = "motor_driver";
    const std::string CONTROL_LOOP_TOPIC   = "control_loop";
} // namespace socket_topics
} // namespace cuuwr::common
