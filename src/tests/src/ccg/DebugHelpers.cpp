#include "ccg/DebugHelpers.hpp"

#include <spdlog/sinks/stdout_sinks.h>


namespace ccg
{
namespace
{

    LoggerPtr InitDebugLogger()
    {
        auto consoleSink = std::make_shared<spdlog::sinks::stdout_sink_st>();
        consoleSink->set_level(spdlog::level::warn);
        consoleSink->set_pattern("[ccg][%l] %v");

        auto logger = std::make_shared<spdlog::logger>("ccg", std::move(consoleSink));
        logger->set_level(spdlog::level::warn);
        spdlog::register_logger(logger);

        return logger;
    }

}  // namespace


LoggerPtr const & MakeDebugLogger()
{
    static auto debugLogger = InitDebugLogger();
    return debugLogger;
}

Context MakeEmptyContext()
{
    return Context{ "", "", "", "", "", "" };
}

Context MakeDummyContext()
{
    return Context{ "./input", "./config", "./out/build", "./out/build/current", ".", "./current" };
}

}  // namespace ccg
