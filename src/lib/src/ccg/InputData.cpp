#include "ccg/InputData.hpp"

#include <fmt/std.h>

#include <nlohmann/json.hpp>

#include <fstream>
#include <istream>


namespace ccg
{

InputData LoadInputData(Context const & context, LoggerPtr const & logger)
{
    if (!std::filesystem::exists(context.inputFile))
    {
        auto message = fmt::format("Input file not found: \"{}\"", context.inputFile);
        logger->error(message);
        throw std::runtime_error(message.c_str());
    }

    return LoadInputData(std::ifstream{ context.inputFile, std::ios::in | std::ios::binary }, context, logger);
}

InputData LoadInputData(std::istream&& stream, Context const& context, LoggerPtr const& logger)
{
    auto json = nlohmann::json::parse(std::move(stream));
    return InputData{ std::move(json) };
}

}  // namespace ccg
