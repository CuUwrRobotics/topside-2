/**
 * @file ControllerManager.cpp
 * @author Cary Keesler
 * @brief
 */

// Header Being Defined
#include <controller/ControllerManager.hpp>

// Third Party Libraries
#include <spdlog/spdlog.h>
#include <zmq.hpp>

// Project Includes
#include <common/ControllerMessages.hpp>
#include <common/SocketInformation.hpp>
#include <common/Unimplemented.hpp>

namespace cuuwr::topside::controller
{
auto ControllerManager::ButtonHandlers::a(const bool isPressed) -> void
{
    spdlog::trace("A button {}pressed", (isPressed ? "" : "un"));

    common::unimplemented("A button has no mapping");
}

auto ControllerManager::ButtonHandlers::b(const bool isPressed) -> void
{
    spdlog::trace("B button {}pressed", (isPressed ? "" : "un"));

    constexpr auto command
        = common::controller_messages::CameraControl::NEXT_CAMERA;

    auto data = zmq::const_buffer(&command, sizeof(command));

    ControllerManager::publish_event(
        common::socket_topics::CAMERA_CONTROL_TOPIC,
        data);
}

auto ControllerManager::ButtonHandlers::x(const bool isPressed) -> void
{
    spdlog::trace("X button {}pressed", (isPressed ? "" : "un"));

    constexpr auto command
        = common::controller_messages::CameraControl::PREVIOUS_CAMERA;

    auto data = zmq::const_buffer(&command, sizeof(command));

    ControllerManager::publish_event(
        common::socket_topics::CAMERA_CONTROL_TOPIC,
        data);
}

auto ControllerManager::ButtonHandlers::y(const bool isPressed) -> void
{
    spdlog::trace("Y button {}pressed", (isPressed ? "" : "un"));

    common::unimplemented("Y button has no mapping");
}

auto ControllerManager::ButtonHandlers::left_bumper(const bool isPressed)
    -> void
{
    spdlog::trace("Left bumper {}pressed", (isPressed ? "" : "un"));

    common::unimplemented("Left bumper has no mapping");
}

auto ControllerManager::ButtonHandlers::right_bumper(const bool isPressed)
    -> void
{
    spdlog::trace("Right bumper {}pressed", (isPressed ? "" : "un"));

    common::unimplemented("Right bumper has no mapping");
}

auto ControllerManager::ButtonHandlers::back(const bool isPressed) -> void
{
    spdlog::trace("Back button {}pressed", (isPressed ? "" : "un"));

    constexpr auto command
        = common::controller_messages::MotorDriver::DISARM_MOTORS;

    auto data = zmq::const_buffer(&command, sizeof(command));

    ControllerManager::publish_event(common::socket_topics::MOTOR_DRIVER_TOPIC,
                                     data);
}

auto ControllerManager::ButtonHandlers::start(const bool isPressed) -> void
{
    spdlog::trace("Start button {}pressed", (isPressed ? "" : "un"));

    constexpr auto command
        = common::controller_messages::MotorDriver::ARM_MOTORS;

    auto data = zmq::const_buffer(&command, sizeof(command));

    ControllerManager::publish_event(common::socket_topics::MOTOR_DRIVER_TOPIC,
                                     data);
}

auto ControllerManager::ButtonHandlers::logo_button(const bool isPressed)
    -> void
{
    spdlog::trace("Logo button {}pressed", (isPressed ? "" : "un"));

    common::unimplemented("Logo button has no mapping");
}

auto ControllerManager::ButtonHandlers::left_joystick(const bool isPressed)
    -> void
{
    spdlog::trace("Left stick {}pressed", (isPressed ? "" : "un"));

    common::unimplemented("Left stick has no mapping");
}

auto ControllerManager::ButtonHandlers::right_joystick(const bool isPressed)
    -> void
{
    spdlog::trace("Right stick {}pressed", (isPressed ? "" : "un"));

    common::unimplemented("Right stick has no mapping");
}
} // namespace cuuwr::topside::controller
