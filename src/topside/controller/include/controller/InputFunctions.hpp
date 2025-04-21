/**
 * @file InputFunctions.hpp
 * @author Cary Keesler
 * @brief
 */

// Standard Library Includes
#include <cstdint>

namespace cuuwr::topside::controller
{
namespace ButtonHandlers
{
    auto a(const bool isPressed) -> void;
    auto b(const bool isPressed) -> void;
    auto x(const bool isPressed) -> void;
    auto y(const bool isPressed) -> void;
    auto left_bumper(const bool isPressed) -> void;
    auto right_bumper(const bool isPressed) -> void;
    auto back(const bool isPressed) -> void;
    auto start(const bool isPressed) -> void;
    auto logo_button(const bool isPressed) -> void;
    auto left_joystick(const bool isPressed) -> void;
    auto right_joystick(const bool isPressed) -> void;
} // namespace ButtonHandlers

namespace AxisHandlers
{
    auto left_joystick_x(const std::int16_t value) -> void;
    auto left_joystick_y(const std::int16_t value) -> void;
    auto left_trigger(const std::int16_t value) -> void;
    auto right_joystick_x(const std::int16_t value) -> void;
    auto right_joystick_y(const std::int16_t value) -> void;
    auto right_trigger(const std::int16_t value) -> void;
    auto d_pad_x(const std::int16_t value) -> void;
    auto d_pad_y(const std::int16_t value) -> void;
} // namespace AxisHandlers
} // namespace cuuwr::topside::controller
