#include "ccg/Input.hpp"

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
        std::string currentItem;
        size_t itemIndex;
        size_t outputIndex;
    };

    [[nodiscard]] Output ParseOutput(nlohmann::json const & json, ParseContext & context)
    {
        if (!json.contains("template"))
        {
            auto message = fmt::format(
                "Unable to parse \"{}\" output {}; missing field \"template\" in {}",
                context.currentItem,
                context.outputIndex,
                context.file);
            context.logger->error(message);
            throw std::runtime_error(std::move(message));
        }

        auto templateName = json["template"].get<std::string>();

        if (!json.contains("output"))
        {
            auto message = fmt::format(
                "Unable to parse \"{}\" output {}; missing field \"items\" in {}",
                context.currentItem,
                templateName,
                context.file);
            context.logger->error(message);
            throw std::runtime_error(std::move(message));
        }

        auto outputPath = json["output"].get<std::string>();
        // ToDo: apply macros

        return Output{ std::move(templateName), std::move(outputPath) };
    }

    [[nodiscard]] std::vector<Output> ParseOutputs(nlohmann::json const & json, ParseContext & context)
    {
        context.outputIndex = 0ul;

        if (!json.is_array())
        {
            return std::vector<Output>{ ParseOutput(json, context) };
        }

        auto results = std::vector<Output>();
        results.reserve(json.size());
        for (auto & output : json)
        {
            results.emplace_back(ParseOutput(output, context));
        }

        return results;
    }

    [[nodiscard]] Item ParseItem(nlohmann::json const & json, ParseContext & context)
    {
        if (!json.contains("name"))
        {
            auto message
                = fmt::format("Unable to parse item {}; missing \"name\" in {}", context.itemIndex, context.file);
            context.logger->error(message);
            throw std::runtime_error(std::move(message));
        }

        context.currentItem = json["name"].get<std::string>();

        if (!json.contains("outputs"))
        {
            auto message = fmt::format(
                "Unable to parse item {} ({}); missing \"outputs\" field in {}",
                context.currentItem,
                context.itemIndex,
                context.file);
            context.logger->error(message);
            throw std::runtime_error(std::move(message));
        }

        if (!json.contains("data"))
        {
            auto message = fmt::format(
                "Unable to parse item {} ({}); missing \"data\" field in {}",
                context.currentItem,
                context.itemIndex,
                context.file);
            context.logger->error(message);
            throw std::runtime_error(std::move(message));
        }

        return Item{ std::move(context.currentItem), ParseOutputs(json["outputs"], context), json["data"] };
    }

    [[nodiscard]] std::vector<Item> ParseItems(nlohmann::json const & json, ParseContext & context)
    {
        if (!json.contains("items"))
        {
            return {};
        }

        auto items = json["items"];
        if (!items.is_array())
        {
            auto message = fmt::format("Unable to parse input; \"items\" is not an array {}", context.file);
            context.logger->error(message);
            throw std::runtime_error(std::move(message));
        }

        auto result = std::vector<Item>();
        result.reserve(items.size());

        for (auto & item : items)
        {
            result.emplace_back(ParseItem(item, context));
            context.itemIndex += 1ul;
        }

        return result;
    }

    [[nodiscard]] std::filesystem::path ParseOutDirectory(nlohmann::json const & json, ParseContext & context)
    {
        if (!json.contains("out"))
        {
            auto message = fmt::format("Unable to parse config; missing \"out\" field in \"{}\"", context.file);
            context.logger->error(message);
            throw std::runtime_error(std::move(message));
        }

        auto const & outDirectory = json["out"];
        if (!outDirectory.is_string())
        {
            auto message
                = fmt::format("Unable to parse config; \"out\" field is not a string in \"{}\"", context.file);
            context.logger->error(message);
            throw std::runtime_error(std::move(message));
        }

        auto path = SubstituteMacros(outDirectory.get<std::string>(), context.context, context.logger);
        // ToDo: check directory exists
        // ToDo: ensure trailing '/'

        return path;
    }

    [[nodiscard]] Input ParseInput(nlohmann::json const & json, ParseContext& context)
    {
        return Input{ ParseOutDirectory(json, context), ParseItems(json, context) };
    }

}  // namespace


Input LoadInput(Context const & context, LoggerPtr const & logger)
{
    if (!std::filesystem::exists(context.inputFile))
    {
        auto message = fmt::format("Input file not found: \"{}\"", context.inputFile);
        logger->error(message);
        throw std::runtime_error(std::move(message));
    }

    auto stream = std::ifstream{ context.inputFile, std::ios::in | std::ios::binary };
    auto json = nlohmann::json::parse(std::move(stream));
    auto parseContext = ParseContext{ context, logger, context.inputFile, "", 0ul, 0ul };

    return ParseInput(json, parseContext);
}

Input LoadInput(std::istream && stream, Context const & context, LoggerPtr const & logger)
{
    auto json = nlohmann::json::parse(std::move(stream));
    auto parseContext = ParseContext{ context, logger, "", "", 0ul, 0ul };

    return ParseInput(json, parseContext);
}

}  // namespace ccg
