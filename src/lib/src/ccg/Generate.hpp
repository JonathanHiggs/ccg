#pragma once

#include "ccg/Config.hpp"
#include "ccg/Context.hpp"
#include "ccg/InputData.hpp"
#include "ccg/Logging.hpp"


namespace ccg
{

/**
 * @brief Renders output for the given input and config
 */
void Generate(InputData const & inputData, Config const & config, Context const & context, LoggerPtr const & logger);

}  // namespace ccg
