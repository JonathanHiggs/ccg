#pragma once

#include <spdlog/spdlog.h>

#include <filesystem>


namespace ccg
{

/**
 * @brief Alias for a shared `spdlog::logger`
 */
using LoggerPtr = std::shared_ptr<spdlog::logger>;


/**
 * @brief Initializes logging
 */
void InitLogging(std::filesystem::path const & logDirectory);

/**
 * @brief Creates a logger for the given name
 */
[[nodiscard]] LoggerPtr MakeLogger(std::string name);

}  // namespace ccg
