/**
 * @file Unimplemented.hpp
 * @author Cary Keesler
 * @brief
 */

// Standard Library Includes
#include <source_location>
#include <string_view>

namespace cuuwr::common
{
/**
 * @brief Prints a message stating that a function is unimplemented. Will only
 * print once, if `unimplemented` is called from the same location a second
 * time, it won't print again.
 *
 * @param message Message to display in log message
 * @param location Location of call to unimplemented
 */
[[maybe_unused]]
auto unimplemented(const std::string_view     message = "",
                   const std::source_location location
                   = std::source_location::current()) -> void;
} // namespace cuuwr::common
