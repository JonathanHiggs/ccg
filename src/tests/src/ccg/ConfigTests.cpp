#include "ccg/Config.hpp"

#include "ccg/DebugHelpers.hpp"

#include <fmt/format.h>
#include <fmt/std.h>
#include <gtest/gtest.h>

#include <sstream>


namespace ccg::tests
{

TEST(ConfigTests, EmptyJsonConfig)
{
    // Arrange
    auto const context = MakeEmptyContext();
    auto const logger = MakeDebugLogger();

    auto input = std::istringstream(R"({})");

    // Act
    auto const result = LoadConfig(std::move(input), context, logger);

    // Assert
    EXPECT_EQ(result.templatesDirs.size(), 0ul);
}

TEST(ConfigTests, SingleStringTemplate)
{
    // Arrange
    auto const context = MakeEmptyContext();
    auto const logger = MakeDebugLogger();

    auto input = std::istringstream(R"({"templates":"./templates"})");

    // Act
    auto const result = LoadConfig(std::move(input), context, logger);

    // Assert
    ASSERT_EQ(result.templatesDirs.size(), 1ul);
    EXPECT_EQ(result.templatesDirs[0ul], "./templates")
        << fmt::format("Expected \"{}\" but was \"{}\"", "./templates", result.templatesDirs[0ul]);
}

TEST(ConfigTests, StringArrayTemplate)
{
    // Arrange
    auto const context = MakeEmptyContext();
    auto const logger = MakeDebugLogger();

    auto input = std::istringstream(R"({"templates":["./templates1","./templates2"]})");

    // Act
    auto const result = LoadConfig(std::move(input), context, logger);

    // Assert
    ASSERT_EQ(result.templatesDirs.size(), 2ul);
    EXPECT_EQ(result.templatesDirs[0ul], "./templates1")
        << fmt::format("Expected \"{}\" but was \"{}\"", "./templates1", result.templatesDirs[0ul]);
    EXPECT_EQ(result.templatesDirs[1ul], "./templates2")
        << fmt::format("Expected \"{}\" but was \"{}\"", "./templates2", result.templatesDirs[0ul]);
}

}  // namespace ccg::tests
