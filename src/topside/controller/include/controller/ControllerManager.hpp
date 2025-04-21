/**
 * @file ControllerManager.hpp
 * @author Cary Keesler
 * @brief
 */
#pragma once

// Project Includes
#include <controller/Controller.hpp>
#include <controller/ControllerInput.hpp>

namespace cuuwr::topside::controller
{
class ControllerManager
{
  public: // Constructors
    ControllerManager();

    ControllerManager(ControllerManager& toCopy)                   = delete;
    auto operator=(ControllerManager& toCopy) -> ControllerManager = delete;

  public:  // Methods
    auto run() -> void;

  private: // Structs
    struct InputVisitor
    {
        auto operator()(const AxisInput& input) -> void;
        auto operator()(const ButtonInput& input) -> void;
    };

  private: // Members
    Controller m_Controller;
};
} // namespace cuuwr::topside::controller
