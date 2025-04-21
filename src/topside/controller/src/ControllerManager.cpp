/**
 * @file ControllerManager.cpp
 * @author Cary Keesler
 * @brief
 */

// Header Being Defined
#include <controller/ControllerManager.hpp>

// Standard Library Includes
#include <stdexcept>

// Third Party Libraries
#include <spdlog/spdlog.h>
#include <zmq.hpp>

namespace cuuwr::topside::controller
{
ControllerManager::ControllerManager()
try
    : m_Controller(),
      m_SocketContext(ControllerManager::IO_THREADS,
                      ControllerManager::MAX_SOCKETS)
{
}
catch (std::runtime_error& re)
{
    throw re;
}
catch (zmq::error_t& zmqe)
{
    spdlog::error("Failed to initialize zmq socket context! Error message: {}",
                  zmqe.what());
    throw zmqe;
}

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

auto ControllerManager::ButtonHandlers::a(const bool isPressed) -> void
{
    spdlog::trace("A button {}pressed", (isPressed ? "" : "un"));
}

auto ControllerManager::ButtonHandlers::b(const bool isPressed) -> void
{
    spdlog::trace("B button {}pressed", (isPressed ? "" : "un"));
}

auto ControllerManager::ButtonHandlers::x(const bool isPressed) -> void
{
    spdlog::trace("X button {}pressed", (isPressed ? "" : "un"));
}

auto ControllerManager::ButtonHandlers::y(const bool isPressed) -> void
{
    spdlog::trace("Y button {}pressed", (isPressed ? "" : "un"));
}

auto ControllerManager::ButtonHandlers::left_bumper(const bool isPressed)
    -> void
{
    spdlog::trace("Left bumper {}pressed", (isPressed ? "" : "un"));
}

auto ControllerManager::ButtonHandlers::right_bumper(const bool isPressed)
    -> void
{
    spdlog::trace("Right bumper {}pressed", (isPressed ? "" : "un"));
}

auto ControllerManager::ButtonHandlers::back(const bool isPressed) -> void
{
    spdlog::trace("Back button {}pressed", (isPressed ? "" : "un"));
}

auto ControllerManager::ButtonHandlers::start(const bool isPressed) -> void
{
    spdlog::trace("Start button {}pressed", (isPressed ? "" : "un"));
}

auto ControllerManager::ButtonHandlers::logo_button(const bool isPressed)
    -> void
{
    spdlog::trace("Logo button {}pressed", (isPressed ? "" : "un"));
}

auto ControllerManager::ButtonHandlers::left_joystick(const bool isPressed)
    -> void
{
    spdlog::trace("Left stick {}pressed", (isPressed ? "" : "un"));
}

auto ControllerManager::ButtonHandlers::right_joystick(const bool isPressed)
    -> void
{
    spdlog::trace("Right stick {}pressed", (isPressed ? "" : "un"));
}

auto ControllerManager::AxisHandlers::left_joystick_x(const std::int16_t value)
    -> void
{
    spdlog::trace("Left x axis moved");
}

auto ControllerManager::AxisHandlers::left_joystick_y(const std::int16_t value)
    -> void
{
    spdlog::trace("Left y axis moved");
}

auto ControllerManager::AxisHandlers::left_trigger(const std::int16_t value)
    -> void
{
    spdlog::trace("Left trigger moved");
}

auto ControllerManager::AxisHandlers::right_joystick_x(const std::int16_t value)
    -> void
{
    spdlog::trace("Right x axis moved");
}

auto ControllerManager::AxisHandlers::right_joystick_y(const std::int16_t value)
    -> void
{
    spdlog::trace("Right y axis moved");
}

auto ControllerManager::AxisHandlers::right_trigger(const std::int16_t value)
    -> void
{
    spdlog::trace("Right trigger moved");
}

auto ControllerManager::AxisHandlers::d_pad_x(const std::int16_t value) -> void
{
    spdlog::trace("D-pad x moved");
}

auto ControllerManager::AxisHandlers::d_pad_y(const std::int16_t value) -> void
{
    spdlog::trace("D-pad y moved");
}

auto ControllerManager::run() -> void
{
    while (true)
    {
        auto input = m_Controller.poll_input();

        if (!input.has_value())
        {
            continue;
        }

        std::visit(InputVisitor(), input.value());
    }
}

} // namespace cuuwr::topside::controller
