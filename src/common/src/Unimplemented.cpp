/**
 * @file Unimplemented.cpp
 * @author Cary Keesler
 * @brief
 */

// Header Being Defined
#include <common/Unimplemented.hpp>

// Standard Library Includes
#include <ranges>
#include <source_location>
#include <string_view>
#include <vector>

// Third Party Includes
#include <spdlog/spdlog.h>

namespace cuuwr::common
{
auto unimplemented(const std::string_view     message,
                   const std::source_location location) -> void
{
    static std::vector<std::source_location> seenLocations;

    const auto containsCurrentLocationPredicate
        = [&location](std::source_location seen_loc)
    {
        return location.line() == seen_loc.line()
            && location.file_name() == seen_loc.file_name();
    };

    if (std::ranges::find_if(seenLocations, containsCurrentLocationPredicate)
        != std::end(seenLocations))
    {
        return;
    }

    spdlog::warn("THIS MESSAGE WILL ONLY DISPLAY ONCE! Function {} [{} line "
                 "{}] is not yet implemented! {}",
                 location.function_name(),
                 location.file_name(),
                 location.line(),
                 (message.empty() ? "" : std::format("Message: {}", message)));

    seenLocations.emplace_back(location);
}
} // namespace cuuwr::common
