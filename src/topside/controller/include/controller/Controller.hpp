/**
 * @file Controller.hpp
 * @author Cary Keesler
 * @brief
 */
#pragma once

// Project Includes
#include <controller/ControllerInput.hpp>

namespace cuuwr::topside::controller
{

class Controller
{
  public: // Constructors
    Controller();

    Controller(Controller&)                    = delete;
    Controller(Controller&&)                   = delete;
    auto operator=(Controller&) -> Controller  = delete;
    auto operator=(Controller&&) -> Controller = delete;

    ~Controller();

  public:  // Methods
    auto poll_input() -> std::optional<ControllerInput>;

  private: // Members
    int m_ControllerFileDescriptor = -1;
};
} // namespace cuuwr::topside::controller
