#include "ccg/Run.hpp"

#include "ccg/Config.hpp"
#include "ccg/Context.hpp"
#include "ccg/Generate.hpp"
#include "ccg/Input.hpp"
#include "ccg/Logging.hpp"

#include <fmt/std.h>
#include <fmt/printf.h>

#include <iostream>


namespace ccg
{

int Run(int argc, char ** argv)
{
    try
    {
        auto const context = MakeContext(argc, argv);
        auto const logger = InitLogging(context.logDirectory);

        logger->info("Running ccg for {}", context.inputFile);
        logger->trace("Directories:");
        logger->trace("input file:           {}", context.inputFile);
        logger->trace("config file:          {}", context.configFile);
        logger->trace("log directory:        {}", context.logDirectory);
        logger->trace("binary dir:           {}", context.binaryDirectory);
        logger->trace("current binary dir:   {}", context.currentBinaryDirectory);
        logger->trace("source dir:           {}", context.sourceDirectory);
        logger->trace("current source dir:   {}", context.currentSourceDirectory);

        auto const config = LoadConfig(context, logger);
        auto input = LoadInput(context, logger);

        Generate(input, config, context, logger);

        return 0;
    }
    catch (std::exception const & ex)
    {
        fmt::print(std::cerr, "Unhandled exception:\n{}", ex.what());
        return 1;
    }
    catch (...)
    {
        return 2;
    }
}

}  // namespace ccg
