#include "ccg/Config.hpp"

#include "ccg/DebugHelpers.hpp"

#include <fmt/format.h>
#include <fmt/std.h>
#include <gtest/gtest.h>

#include <sstream>


namespace ccg::tests
{

TEST(ConfigTests, MissingTemplatesDirectoryThrows)
{
    // Arrange
    auto const context = MakeEmptyContext();
    auto const logger = MakeDebugLogger();

    auto input = std::istringstream(R"({})");

    // Act & Assert
    EXPECT_ANY_THROW(std::ignore = LoadConfig(std::move(input), context, logger));
}

TEST(ConfigTests, TemplatesAndNoData)
{
    // Arrange
    auto const context = MakeEmptyContext();
    auto const logger = MakeDebugLogger();

    auto input = std::istringstream(R"({"templates":"./templates"})");

    // Act
    auto const result = LoadConfig(std::move(input), context, logger);

    // Assert
    EXPECT_EQ(result.templatesDirectory, "./templates")
        << fmt::format("Expected \"{}\" but was \"{}\"", "./templates", result.templatesDirectory);
}

}  // namespace ccg::tests
