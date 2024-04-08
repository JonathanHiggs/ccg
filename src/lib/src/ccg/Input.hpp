#pragma once

#include "ccg/Context.hpp"
#include "ccg/Logging.hpp"

#include <nlohmann/json.hpp>

#include <iosfwd>


namespace ccg
{

struct Output final
{
    std::string templateName;
    std::string outputPath;
};


struct Item final
{
    std::string name;
    std::vector<Output> outputs;
    nlohmann::json data;
};


struct Input final
{
    std::filesystem::path outDirectory;
    std::vector<Item> items;
};


/**
 * @brief Loads `ccg::Input` from `ccg::Context::inputPath`
 */
[[nodiscard]] Input LoadInput(Context const & context, LoggerPtr const & logger);


/**
 * @brief Loads `ccg::Input` from the supplied `std::istream`
 */
[[nodiscard]] Input LoadInput(std::istream && stream, Context const & context, LoggerPtr const & logger);

}  // namespace ccg
