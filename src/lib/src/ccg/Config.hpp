#pragma once

#include "ccg/Context.hpp"
#include "ccg/Logging.hpp"

#include <filesystem>
#include <iosfwd>
#include <vector>


namespace ccg
{

/**
 * @brief Configuration settings passed to and used to control file generation
 */
struct Config final
{
    std::vector<std::filesystem::path> templatesDirs;
};


/**
 * @brief Loads `ccg::Config` from `ccg::Config::configPath`
 */
[[nodiscard]] Config LoadConfig(Context const & context, LoggerPtr const & logger);


/**
 * @brief Loads `ccg::Config` from the supplied `std::istream`
 */
[[nodiscard]] Config LoadConfig(std::istream && stream, Context const & context, LoggerPtr const & logger);

}  // namespace ccg
