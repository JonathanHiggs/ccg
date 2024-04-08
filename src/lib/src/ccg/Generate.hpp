#pragma once

#include "ccg/Config.hpp"
#include "ccg/Context.hpp"
#include "ccg/Input.hpp"
#include "ccg/Logging.hpp"


namespace ccg
{

/**
 * @brief Renders output for the given input and config
 */
void Generate(Input & input, Config const & config, Context const & context, LoggerPtr const & logger);

}  // namespace ccg
