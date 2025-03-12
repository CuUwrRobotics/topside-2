/**
 * @file Controller.hpp
 * @author Cary Keesler
 * @brief
 */
#pragma once

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

  private:
    int m_ControllerFileDescriptor = -1;
};
} // namespace cuuwr::topside::controller
