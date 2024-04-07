#include "ccg/Logging.hpp"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/spdlog.h>


namespace ccg
{
namespace
{

    static bool initialized = false;
    static std::shared_ptr<spdlog::sinks::basic_file_sink_st> outputSink;
    static std::shared_ptr<spdlog::sinks::basic_file_sink_st> errorSink;
    static std::shared_ptr<spdlog::sinks::stdout_sink_st> consoleSink;
    
}


void InitLogging(std::filesystem::path const & logDirectory)
{  
    auto const fixedPath = std::filesystem::absolute(logDirectory).make_preferred();
    if (!std::filesystem::exists(fixedPath))
    {
        std::filesystem::create_directories(fixedPath);
    }

    auto outputFile = fixedPath / "ccg.output.log";
    outputSink = std::make_shared<spdlog::sinks::basic_file_sink_st>(outputFile.string(), true);
    outputSink->set_level(spdlog::level::info);
    outputSink->set_pattern("[%l] %v");

    auto errorFile = fixedPath / "ccg.error.log";
    errorSink = std::make_shared<spdlog::sinks::basic_file_sink_st>(errorFile.string(), true);
    errorSink->set_level(spdlog::level::trace);
    errorSink->set_pattern("[%l] %v");

    consoleSink = std::make_shared<spdlog::sinks::stdout_sink_st>();
    consoleSink->set_level(spdlog::level::warn);
    consoleSink->set_pattern("[ccg][%l] %v");

    initialized = true;
}

[[nodiscard]] std::shared_ptr<spdlog::logger> MakeLogger(std::string name)
{
    if (!initialized)
    {
        throw std::runtime_error("Logging is not initialized");
    }

    auto logger = std::make_shared<spdlog::logger>(
        std::move(name),
        std::initializer_list<spdlog::sink_ptr>{ outputSink, errorSink, consoleSink });

    logger->set_level(spdlog::level::trace);
    logger->trace("Initialized logging");

    spdlog::register_logger(logger);

    return logger;
}

}  // namespace ccg
