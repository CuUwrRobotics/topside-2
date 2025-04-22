/**
 * @file ControllerManager/AxisHandlers.cpp
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
auto ControllerManager::AxisHandlers::left_joystick_x(const std::int16_t value)
    -> void
{
    spdlog::trace("Left x axis moved");

    s_StickInterpreter.set_left_x(value);
    auto goal_vec = s_StickInterpreter.get_goal_vector();

    auto data = zmq::const_buffer(&goal_vec, sizeof(goal_vec));

    ControllerManager::publish_event(common::socket_topics::CONTROL_LOOP_TOPIC,
                                     data);
}

auto ControllerManager::AxisHandlers::left_joystick_y(const std::int16_t value)
    -> void
{
    spdlog::trace("Left y axis moved");

    s_StickInterpreter.set_left_y(value);
    auto goal_vec = s_StickInterpreter.get_goal_vector();

    auto data = zmq::const_buffer(&goal_vec, sizeof(goal_vec));

    ControllerManager::publish_event(common::socket_topics::CONTROL_LOOP_TOPIC,
                                     data);
}

auto ControllerManager::AxisHandlers::left_trigger(const std::int16_t value)
    -> void
{
    spdlog::trace("Left trigger moved");

    common::unimplemented("Left trigger has no mapping");
}

auto ControllerManager::AxisHandlers::right_joystick_x(const std::int16_t value)
    -> void
{
    spdlog::trace("Right x axis moved");

    s_StickInterpreter.set_right_x(value);
    auto goal_vec = s_StickInterpreter.get_goal_vector();

    auto data = zmq::const_buffer(&goal_vec, sizeof(goal_vec));

    ControllerManager::publish_event(common::socket_topics::CONTROL_LOOP_TOPIC,
                                     data);
}

auto ControllerManager::AxisHandlers::right_joystick_y(const std::int16_t value)
    -> void
{
    spdlog::trace("Right y axis moved");

    s_StickInterpreter.set_right_y(value);
    auto goal_vec = s_StickInterpreter.get_goal_vector();

    auto data = zmq::const_buffer(&goal_vec, sizeof(goal_vec));

    ControllerManager::publish_event(common::socket_topics::CONTROL_LOOP_TOPIC,
                                     data);
}

auto ControllerManager::AxisHandlers::right_trigger(const std::int16_t value)
    -> void
{
    spdlog::trace("Right trigger moved");

    common::unimplemented("Right trigger has no mapping");
}

auto ControllerManager::AxisHandlers::d_pad_x(const std::int16_t value) -> void
{
    spdlog::trace("D-pad x moved");

    common::unimplemented("D-pad x has no mapping");
}

auto ControllerManager::AxisHandlers::d_pad_y(const std::int16_t value) -> void
{
    spdlog::trace("D-pad y moved");

    common::unimplemented("D-pad y has no mapping");
}
} // namespace cuuwr::topside::controller
