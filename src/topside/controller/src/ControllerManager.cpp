/**
 * @file ControllerManager.cpp
 * @author Cary Keesler
 * @brief
 */

// Header Being Defined
#include <controller/ControllerManager.hpp>

// Standard Library Includes
#include <stdexcept>

// Third Party Libraries
#include <spdlog/spdlog.h>
#include <zmq.hpp>

// Project Includes
#include <common/SocketInformation.hpp>

namespace cuuwr::topside::controller
{
ControllerManager::ControllerManager()
try
    : m_Controller()
{
    spdlog::info("Initialized zmq socket context");

    const auto controllerEventPublisherAddress
        = std::format("tcp://*:{}", common::socket_ports::CONTROLLER_PUBLISHER);

    spdlog::debug(
        "Attempting to bind controller event publisher socket to address {}",
        controllerEventPublisherAddress);

    s_ControllerEventPublisher.bind(controllerEventPublisherAddress);

    spdlog::info(
        "Successfully bound controller event publisher socket on address {}!",
        controllerEventPublisherAddress);
}
catch (std::runtime_error& re)
{
    throw re;
}
catch (zmq::error_t& zmqe)
{
    spdlog::error("zmq operation failed! Error message: {}", zmqe.what());
    throw zmqe;
}

auto ControllerManager::publish_event(const std::string&       topic,
                                      const zmq::const_buffer& data) -> void
{
    s_ControllerEventPublisher.send(zmq::message_t(topic),
                                    zmq::send_flags::sndmore);
    s_ControllerEventPublisher.send(data);
}

auto ControllerManager::run() -> void
{
    while (true)
    {
        auto input = m_Controller.poll_input();

        if (!input.has_value())
        {
            continue;
        }

        std::visit(InputVisitor(), input.value());
    }
}
} // namespace cuuwr::topside::controller
