#include "ccg/Macros.hpp"

#include "ccg/DebugHelpers.hpp"

#include <gtest/gtest.h>


using namespace std::string_literals;


namespace ccg::tests
{

TEST(MacroTests, SubstituteMacrosWithEmpty)
{
    // Arrange
    auto const source = ""s;
    auto const expected = ""s;

    auto const context = MakeDummyContext();
    auto const logger = MakeDebugLogger();

    // Act
    auto const result = SubstituteMacros(source, context, logger);

    // Assert
    EXPECT_EQ(result, expected) << fmt::format("Expected \"{}\" but was \"{}\"", expected, result);
}

TEST(MacroTests, SubstituteMacrosWithNoMacros)
{
    // Arrange
    auto const source = "./some/path"s;
    auto const expected = "./some/path"s;

    auto const context = MakeDummyContext();
    auto const logger = MakeDebugLogger();

    // Act
    auto const result = SubstituteMacros(source, context, logger);

    // Assert
    EXPECT_EQ(result, expected) << fmt::format("Expected \"{}\" but was \"{}\"", expected, result);
}

TEST(MacroTests, SubstituteMacrosWithSourceDir)
{
    // Arrange
    auto const source = "${sourceDir}/some/path"s;
    auto const expected = "./some/path"s;

    auto const context = MakeDummyContext();
    auto const logger = MakeDebugLogger();

    // Act
    auto const result = SubstituteMacros(source, context, logger);

    // Assert
    EXPECT_EQ(result, expected) << fmt::format("Expected \"{}\" but was \"{}\"", expected, result);
}

TEST(MacroTests, SubstituteMacrosWithBinaryDir)
{
    // Arrange
    auto const source = "${binaryDir}/some/path"s;
    auto const expected = "./out/build/some/path"s;

    auto const context = MakeDummyContext();
    auto const logger = MakeDebugLogger();

    // Act
    auto const result = SubstituteMacros(source, context, logger);

    // Assert
    EXPECT_EQ(result, expected) << fmt::format("Expected \"{}\" but was \"{}\"", expected, result);
}

}  // namespace ccg::tests
