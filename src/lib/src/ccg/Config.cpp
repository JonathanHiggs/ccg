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

    /**
     * @brief Temporary parsing info to help with error feedback
     */
    struct ParseContext final
    {
        Context const & context;
        LoggerPtr const & logger;

        std::filesystem::path file;
    };

    [[nodiscard]] std::filesystem::path ParseTemplatesDirectory(nlohmann::json const & json, ParseContext & context)
    {
        if (!json.contains("templates"))
        {
            auto message = fmt::format("Unable to parse config; missing \"templates\" field in \"{}\"", context.file);
            context.logger->error(message);
            throw std::runtime_error(std::move(message));
        }

        auto const & templates = json["templates"];
        if (!templates.is_string())
        {
            auto message
                = fmt::format("Unable to parse config; \"templates\" field is not a string in \"{}\"", context.file);
            context.logger->error(message);
            throw std::runtime_error(std::move(message));
        }

        auto path = SubstitutePathMacros(templates.get<std::string>(), context.context, context.logger);
        // ToDo: check directory exists
        // ToDo: ensure trailing '/'

        return path;
    }

    [[nodiscard]] nlohmann::json ParseData(nlohmann::json const & json, ParseContext &)
    {
        if (!json.contains("data"))
        {
            return {};
        }

        return json["data"];
    }

    [[nodiscard]] Config ParseConfig(nlohmann::json const & json, ParseContext & context)
    {
        return Config{ ParseTemplatesDirectory(json, context), ParseData(json, context) };
    }

}  // namespace


Config LoadConfig(Context const & context, LoggerPtr const & logger)
{
    if (!std::filesystem::exists(context.configFile))
    {
        auto message = fmt::format("Config file not found: \"{}\"", context.configFile);
        logger->error(message);
        throw std::runtime_error(std::move(message));
    }

    auto stream = std::ifstream{ context.configFile, std::ios::in | std::ios::binary };
    auto json = nlohmann::json::parse(std::move(stream));
    auto parseContext = ParseContext{ context, logger, context.configFile };

    return ParseConfig(json, parseContext);
}

[[nodiscard]] Config LoadConfig(std::istream && stream, Context const & context, LoggerPtr const & logger)
{
    auto json = nlohmann::json::parse(std::move(stream));
    auto parseContext = ParseContext{ context, logger, "" };

    return ParseConfig(json, parseContext);
}

}  // namespace ccg
