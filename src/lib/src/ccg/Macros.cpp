#include "ccg/Macros.hpp"

#include <regex>
#include <sstream>


using namespace std::string_view_literals;


namespace ccg
{
namespace
{

    [[nodiscard]] bool Apply(std::stringstream & stream, std::string_view name, Context const & context)
    {
        if (name == "binaryDir"sv)
        {
            stream << context.binaryDirectory.string();
            return true;
        }
        if (name == "currentBinaryDir"sv)
        {
            stream << context.currentBinaryDirectory.string();
            return true;
        }
        if (name == "sourceDir"sv)
        {
            stream << context.sourceDirectory.string();
            return true;
        }
        if (name == "currentSourceDir"sv)
        {
            stream << context.currentSourceDirectory.string();
            return true;
        }

        return false;
    }

}  // namespace


std::string SubstituteMacros(std::string const & source, Context const & context, LoggerPtr const & logger)
{
    static auto pattern = std::regex(R"(\$\{([a-zA-Z]+)\})");

    std::smatch match;
    size_t position = 0ul;

    auto stream = std::stringstream{};
    auto temp = source;

    while (std::regex_search(temp, match, pattern))
    {
        stream << match.prefix();

        auto name = std::string_view(temp.data() + match.position(1ul), static_cast<size_t>(match.length(1ul)));
        auto result = Apply(stream, name, context);

        if (!result)
        {
            auto message = fmt::format("Macro substitution failed, unrecognised macro \"{}\" in {}", name, source);
            logger->error(message);
            throw std::runtime_error(std::move(message));
        }

        position += static_cast<size_t>(match.position() + match.length());
        temp = source.substr(position);
    }

    stream << source.substr(position);

    auto result = stream.str();

    logger->trace("Substituted from \"{}\" to \"{}\"", source, result);

    return result;
}

std::filesystem::path SubstitutePathMacros(
    std::string const & source, Context const & context, LoggerPtr const & logger)
{
    return std::filesystem::path(SubstituteMacros(source, context, logger)).make_preferred();
}

}  // namespace ccg
