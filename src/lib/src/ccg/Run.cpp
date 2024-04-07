#include "ccg/Run.hpp"

#include "ccg/Config.hpp"
#include "ccg/Context.hpp"
#include "ccg/Generate.hpp"
#include "ccg/InputData.hpp"
#include "ccg/Logging.hpp"


namespace ccg
{

int Run(int argc, char ** argv)
{
    try
    {
        auto const context = MakeContext(argc, argv);

        InitLogging(context.currentBinaryDir / "ccg");
        auto const logger = MakeLogger("ccg");

        auto const config = LoadConfig(context, logger);
        auto const inputData = LoadInputData(context, logger);

        Generate(inputData, config, context, logger);

        return 0;
    }
    catch (std::exception const &)
    {
        return 1;
    }
    catch (...)
    {
        return 2;
    }
}

}  // namespace ccg
