/**
 * @file ControllerManager.hpp
 * @author Cary Keesler
 * @brief
 */
#pragma once

// Project Includes
#include <controller/Controller.hpp>

namespace cuuwr::topside::controller
{
class ControllerManager
{
  public:
    ControllerManager();

    ControllerManager(ControllerManager& toCopy)                   = delete;
    auto operator=(ControllerManager& toCopy) -> ControllerManager = delete;

  private:
    Controller m_Controller;
};
} // namespace cuuwr::topside::controller
