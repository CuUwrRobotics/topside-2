/**
 * @file ControllerManager.cpp
 * @author Cary Keesler
 * @brief
 */

// Header Being Defined
#include <controller/ControllerManager.hpp>

// Project Includes
#include <controller/LogitechF310Mappings.hpp>

namespace cuuwr::topside::controller
{
auto ControllerManager::InputVisitor::operator()(const AxisInput& input) -> void
{
    switch (input.axis)
    {
    case ControllerAxis::LEFT_JOYSTICK_X:
        AxisHandlers::left_joystick_x(input.position);
        break;
    case ControllerAxis::LEFT_JOYSTICK_Y:
        AxisHandlers::left_joystick_y(input.position);
        break;
    case ControllerAxis::LEFT_TRIGGER:
        AxisHandlers::left_trigger(input.position);
        break;
    case ControllerAxis::RIGHT_JOYSTICK_X:
        AxisHandlers::right_joystick_x(input.position);
        break;
    case ControllerAxis::RIGHT_JOYSTICK_Y:
        AxisHandlers::right_joystick_y(input.position);
        break;
    case ControllerAxis::RIGHT_TRIGGER:
        AxisHandlers::right_trigger(input.position);
        break;
    case ControllerAxis::D_PAD_X:
        AxisHandlers::d_pad_x(input.position);
        break;
    case ControllerAxis::D_PAD_Y:
        AxisHandlers::d_pad_y(input.position);
        break;
    }
}

auto ControllerManager::InputVisitor::operator()(const ButtonInput& input)
    -> void
{
    switch (input.button)
    {
    case ControllerButton::A:
        ButtonHandlers::a(input.isPressed);
        break;
    case ControllerButton::B:
        ButtonHandlers::b(input.isPressed);
        break;
    case ControllerButton::X:
        ButtonHandlers::x(input.isPressed);
        break;
    case ControllerButton::Y:
        ButtonHandlers::y(input.isPressed);
        break;
    case ControllerButton::LEFT_BUMPER:
        ButtonHandlers::left_bumper(input.isPressed);
        break;
    case ControllerButton::RIGHT_BUMPER:
        ButtonHandlers::right_bumper(input.isPressed);
        break;
    case ControllerButton::BACK:
        ButtonHandlers::back(input.isPressed);
        break;
    case ControllerButton::START:
        ButtonHandlers::start(input.isPressed);
        break;
    case ControllerButton::LOGO_BUTTON:
        ButtonHandlers::logo_button(input.isPressed);
        break;
    case ControllerButton::LEFT_JOYSTICK:
        ButtonHandlers::left_joystick(input.isPressed);
        break;
    case ControllerButton::RIGHT_JOYSTICK:
        ButtonHandlers::right_joystick(input.isPressed);
        break;
    }
}
} // namespace cuuwr::topside::controller
