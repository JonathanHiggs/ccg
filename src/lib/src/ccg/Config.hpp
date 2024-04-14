#pragma once

#include "ccg/Context.hpp"
#include "ccg/Logging.hpp"

#include <nlohmann/json.hpp>

#include <filesystem>
#include <iosfwd>


namespace ccg
{

/**
 * @brief Configuration settings used to control file generation
 */
struct Config final
{
    std::filesystem::path templatesDirectory;

    // Maybe:
    // bool trimBlocks;
    // bool lstripBlocks;

    nlohmann::json data;
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
