// Header Being Defined
#include <controller/ControllerManager.hpp>

// Standard Library Includes
#include <stdexcept>

namespace cuuwr::topside::controller
{
ControllerManager::ControllerManager()
try
    : m_Controller()
{
}
catch (std::runtime_error& re)
{
    throw re;
}

auto ControllerManager::InputVisitor::operator()(const AxisInput& input) -> void
{
}

auto ControllerManager::InputVisitor::operator()(const ButtonInput& input)
    -> void
{
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
