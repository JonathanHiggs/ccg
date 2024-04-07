#pragma once

#include "ccg/Context.hpp"
#include "ccg/Logging.hpp"

#include <nlohmann/json.hpp>

#include <iosfwd>


namespace ccg
{

struct InputData final
{
    nlohmann::json data;
};


/**
 * @brief Loads `ccg::InputData` from `ccg::Context::inputPath`
 */
[[nodiscard]] InputData LoadInputData(Context const & context, LoggerPtr const & logger);


/**
 * @brief Loads `ccg::InputData` from the supplied `std::istream`
 */
[[nodiscard]] InputData LoadInputData(std::istream && stream, Context const & context, LoggerPtr const & logger);

}  // namespace ccg
