#pragma once

#include "ccg/Context.hpp"
#include "ccg/Logging.hpp"


namespace ccg
{

/**
 * @brief Returns a logger that only outputs to the console
 */
[[nodiscard]] LoggerPtr const & MakeDebugLogger();


/**
 * @brief Returns an empty context
 */
[[nodiscard]] Context MakeEmptyContext();

}  // namespace ccg
