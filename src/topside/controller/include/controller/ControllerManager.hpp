/**
 * @file ControllerManager.hpp
 * @author Cary Keesler
 * @brief
 */
#pragma once

// Third Party Libraries
#include <zmq.hpp>

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

  private: // Static Members
    static inline constexpr int IO_THREADS  = 1;
    static inline constexpr int MAX_SOCKETS = 2;

  private: // Members
    Controller     m_Controller;
    zmq::context_t m_SocketContext;
};
} // namespace cuuwr::topside::controller
