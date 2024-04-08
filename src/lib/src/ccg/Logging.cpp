#include "ccg/Logging.hpp"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/spdlog.h>


namespace ccg
{

LoggerPtr InitLogging(std::filesystem::path const & logDirectory)
{
    if (!std::filesystem::exists(logDirectory))
    {
        std::filesystem::create_directories(logDirectory);
    }

    auto outputFile = logDirectory / "output.log";
    auto outputSink = std::make_shared<spdlog::sinks::basic_file_sink_st>(outputFile.string(), true);
    outputSink->set_level(spdlog::level::info);
    outputSink->set_pattern("[%l] %v");

    auto errorFile = logDirectory / "error.log";
    auto errorSink = std::make_shared<spdlog::sinks::basic_file_sink_st>(errorFile.string(), true);
    errorSink->set_level(spdlog::level::trace);
    errorSink->set_pattern("[%l] %v");

    auto consoleSink = std::make_shared<spdlog::sinks::stdout_sink_st>();
    consoleSink->set_level(spdlog::level::warn);
    consoleSink->set_pattern("[ccg][%l] %v");

    auto logger = std::make_shared<spdlog::logger>(
        "ccg",
        std::initializer_list<spdlog::sink_ptr>{ std::move(outputSink), std::move(errorSink), std::move(consoleSink) });

    logger->set_level(spdlog::level::trace);
    logger->trace("Initialized logging");

    spdlog::register_logger(logger);

    return logger;
}

}  // namespace ccg
