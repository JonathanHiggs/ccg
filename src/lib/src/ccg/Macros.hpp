#pragma once

#include "ccg/Context.hpp"
#include "ccg/Logging.hpp"

#include <string>
#include <filesystem>


namespace ccg
{

/**
 * @brief Applies string macro substitution to the source string
 */
[[nodiscard]] std::string SubstituteMacros(
    std::string const & source, Context const & context, LoggerPtr const & logger);

/**
 * @brief Applies string macro substitution to the source string
 */
[[nodiscard]] std::filesystem::path SubstitutePathMacros(
    std::string const & source, Context const & context, LoggerPtr const & logger);

}  // namespace ccg
