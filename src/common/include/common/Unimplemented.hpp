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
auto unimplemented(const std::string_view&    message = "",
                   const std::source_location location
                   = std::source_location::current()) -> void;
} // namespace cuuwr::common
