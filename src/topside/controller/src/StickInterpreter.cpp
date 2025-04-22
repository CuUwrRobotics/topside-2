/**
 * @file StickInterpreter.cpp
 * @author Cary Keesler
 * @brief
 */

// Header Being Defined
#include <controller/StickInterpreter.hpp>

// Project Includes
#include <common/Unimplemented.hpp>

namespace cuuwr::topside::controller
{
auto StickInterpreter::get_goal_vector() -> common::Vector3
{
    common::unimplemented();

    return { .x = 0.0, .y = 0.0, .z = 0.0 };
}
} // namespace cuuwr::topside::controller
