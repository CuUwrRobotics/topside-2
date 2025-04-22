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
#include <controller/StickInterpreter.hpp>

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

    struct ButtonHandlers
    {
        static auto a(const bool isPressed) -> void;
        static auto b(const bool isPressed) -> void;
        static auto x(const bool isPressed) -> void;
        static auto y(const bool isPressed) -> void;
        static auto left_bumper(const bool isPressed) -> void;
        static auto right_bumper(const bool isPressed) -> void;
        static auto back(const bool isPressed) -> void;
        static auto start(const bool isPressed) -> void;
        static auto logo_button(const bool isPressed) -> void;
        static auto left_joystick(const bool isPressed) -> void;
        static auto right_joystick(const bool isPressed) -> void;
    };

    struct AxisHandlers
    {
        static auto left_joystick_x(const std::int16_t value) -> void;
        static auto left_joystick_y(const std::int16_t value) -> void;
        static auto left_trigger(const std::int16_t value) -> void;
        static auto right_joystick_x(const std::int16_t value) -> void;
        static auto right_joystick_y(const std::int16_t value) -> void;
        static auto right_trigger(const std::int16_t value) -> void;
        static auto d_pad_x(const std::int16_t value) -> void;
        static auto d_pad_y(const std::int16_t value) -> void;
    };

  private: // Methods
    static auto publish_event(const std::string&       topic,
                              const zmq::const_buffer& data) -> void;

  private: // Static Members
    static inline constexpr int  IO_THREADS  = 1;
    static inline constexpr int  MAX_SOCKETS = 3;
    static inline zmq::context_t s_SocketContext {
        ControllerManager::IO_THREADS,
        ControllerManager::MAX_SOCKETS
    };
    static inline zmq::socket_t s_ControllerEventPublisher {
        s_SocketContext,
        zmq::socket_type::pub
    };
    static inline StickInterpreter s_StickInterpreter;

  private: // Members
    Controller m_Controller;
};
} // namespace cuuwr::topside::controller
