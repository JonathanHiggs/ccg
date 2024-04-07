#include "ccg/Config.hpp"
#include "ccg/Macros.hpp"

#include <fmt/std.h>

#include <nlohmann/json.hpp>

#include <fstream>
#include <istream>


namespace ccg
{
namespace
{

    [[nodiscard]] std::filesystem::path ParseTemplatePath(
        nlohmann::json const& json, Context const& context, LoggerPtr const& logger)
    {
        if (!json.is_string())
        {
            throw std::runtime_error(
                "Unable to parse config template path; should be a string");
        }

        auto value = json.get<std::string>();
        value = SubstituteMacros(value, context, logger);

        return std::filesystem::path(value).make_preferred();
    }

    [[nodiscard]] std::vector<std::filesystem::path> ParseTemplatesDirs(
        nlohmann::json const & json, Context const & context, LoggerPtr const & logger)
    {
        auto result = std::vector<std::filesystem::path>();
        if (json.contains("templates"))
        {
            auto const & templates = json["templates"];
            if (templates.is_array())
            {
                result.reserve(templates.size());

                for (auto const & path : templates)
                {
                    if (!path.is_string())
                    {
                        throw std::runtime_error("Unable to parse config template path; not a string");
                    }

                    result.emplace_back(ParseTemplatePath(path, context, logger));
                }
            }
            else if (templates.is_string())
            {
                result.emplace_back(ParseTemplatePath(templates, context, logger));
            }
            else
            {
                throw std::runtime_error(
                    "Unable to parse config templates paths; should be a string or an array of strings");
            }
        }

        return result;
    }

}  // namespace


Config LoadConfig(Context const & context, LoggerPtr const & logger)
{
    if (!std::filesystem::exists(context.configFile))
    {
        auto message = fmt::format("Config file not found: \"{}\"", context.configFile);
        logger->error(message);
        throw std::runtime_error(message.c_str());
    }

    return LoadConfig(std::ifstream{ context.configFile, std::ios::in | std::ios::binary }, context, logger);
}

[[nodiscard]] Config LoadConfig(std::istream && stream, Context const & context, LoggerPtr const & logger)
{
    auto const & json = nlohmann::json::parse(std::move(stream));
    return Config{ ParseTemplatesDirs(json, context, logger) };
}

}  // namespace ccg
