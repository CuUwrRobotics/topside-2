/**
 * @file StickInterpreter.hpp
 * @author Cary Keesler
 * @brief
 */

#pragma once

// Standard Library Includes
#include <cstdint>

// Project Includes
#include <common/Vector3.hpp>

namespace cuuwr::topside::controller
{
class StickInterpreter
{
  public: // Constructors
    StickInterpreter() { }

    StickInterpreter(StickInterpreter& other)                   = delete;
    auto operator=(StickInterpreter& other) -> StickInterpreter = delete;

  public: // Methods
    // TODO: Check if thats the right name
    [[nodiscard]]
    auto get_goal_vector() -> common::Vector3;

    inline auto set_left_x(const std::int16_t value) -> void
    {
        LeftStick.xPosition = value;
    }

    inline auto set_left_y(const std::int16_t value) -> void
    {
        LeftStick.yPosition = value;
    }

    inline auto set_right_x(const std::int16_t value) -> void
    {
        RightStick.xPosition = value;
    }

    inline auto set_right_y(const std::int16_t value) -> void
    {
        RightStick.yPosition = value;
    }

  private: // Structs
    struct Stick
    {
        std::int16_t xPosition;
        std::int16_t yPosition;
    };

  private: // Members
    Stick LeftStick;
    Stick RightStick;
};
} // namespace cuuwr::topside::controller
