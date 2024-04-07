#pragma once

#include "ccg/Context.hpp"
#include "ccg/Logging.hpp"


namespace ccg
{

/**
 * @brief Applies string macro substitution to the source string
 */
[[nodiscard]] std::string SubstituteMacros(std::string_view source, Context const & context, LoggerPtr const & logger);

}
