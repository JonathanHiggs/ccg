#include "ccg/Input.hpp"

#include "ccg/DebugHelpers.hpp"

#include <fmt/format.h>
#include <fmt/std.h>
#include <gtest/gtest.h>

#include <sstream>


namespace ccg::tests
{

TEST(InputTests, LoadInputWithEmptyJson)
{
    // Arrange
    auto const context = MakeEmptyContext();
    auto const logger = MakeDebugLogger();

    auto input = std::istringstream(R"({})");

    // Act & Assert
    EXPECT_ANY_THROW(auto _ = LoadInput(std::move(input), context, logger));
}

TEST(InputTests, ParseSingleOutput)
{
    // Arrange
    auto const context = MakeEmptyContext();
    auto const logger = MakeDebugLogger();

    auto input = std::istringstream(R"({
  "out": "out/files",
  "items":[
    {
      "name": "item1",
      "outputs": [
        {
          "template": "t1",
          "output":"item1.cpp"
        }
      ],
      "data": {}
    }
  ]
})");

    // Act
    auto const result = LoadInput(std::move(input), context, logger);

    // Assert
    ASSERT_EQ(result.items.size(), 1ul);

    EXPECT_EQ(result.items[0ul].name, "item1");
    ASSERT_EQ(result.items[0ul].outputs.size(), 1ul);
    EXPECT_EQ(result.items[0ul].outputs[0ul].templateName, "t1");
    EXPECT_EQ(result.items[0ul].outputs[0ul].outputPath, "item1.cpp");
    EXPECT_TRUE(result.items[0ul].data.empty());
}

TEST(InputTests, ParseMultipleOutputs)
{
    // Arrange
    auto const context = MakeEmptyContext();
    auto const logger = MakeDebugLogger();

    auto input = std::istringstream(R"({
  "out": "out/files",
  "items":[
    {
      "name": "item1",
      "outputs": [
        {
          "template": "t1",
          "output":"out.cpp"
        },
        {
          "template": "t2",
          "output": "out.hpp"
        }
      ],
      "data": {}
    }
  ]
})");

    // Act
    auto const result = LoadInput(std::move(input), context, logger);

    // Assert
    ASSERT_EQ(result.items.size(), 1ul);

    EXPECT_EQ(result.items[0ul].name, "item1");
    ASSERT_EQ(result.items[0ul].outputs.size(), 2ul);
    EXPECT_EQ(result.items[0ul].outputs[0ul].templateName, "t1");
    EXPECT_EQ(result.items[0ul].outputs[0ul].outputPath, "out.cpp");
    EXPECT_EQ(result.items[0ul].outputs[1ul].templateName, "t2");
    EXPECT_EQ(result.items[0ul].outputs[1ul].outputPath, "out.hpp");
    EXPECT_TRUE(result.items[0ul].data.empty());
}

TEST(InputTests, ParseMultipleItems)
{
    // Arrange
    auto const context = MakeEmptyContext();
    auto const logger = MakeDebugLogger();

    auto input = std::istringstream(R"({
  "out": "out/files",
  "items":[
    {
      "name": "item1",
      "outputs": [
        {
          "template": "t1",
          "output":"item1.cpp"
        },
        {
          "template": "t2",
          "output": "item1.hpp"
        }
      ],
      "data": {}
    },
    {
      "name": "item2",
      "outputs": [
        {
          "template": "t1",
          "output":"item2.cpp"
        }
      ],
      "data": {}
    }
  ]
})");

    // Act
    auto const result = LoadInput(std::move(input), context, logger);

    // Assert
    ASSERT_EQ(result.items.size(), 2ul);

    EXPECT_EQ(result.items[0ul].name, "item1");
    ASSERT_EQ(result.items[0ul].outputs.size(), 2ul);
    EXPECT_EQ(result.items[0ul].outputs[0ul].templateName, "t1");
    EXPECT_EQ(result.items[0ul].outputs[0ul].outputPath, "item1.cpp");
    EXPECT_EQ(result.items[0ul].outputs[1ul].templateName, "t2");
    EXPECT_EQ(result.items[0ul].outputs[1ul].outputPath, "item1.hpp");
    EXPECT_TRUE(result.items[0ul].data.empty());

    EXPECT_EQ(result.items[1ul].name, "item2");
    ASSERT_EQ(result.items[1ul].outputs.size(), 1ul);
    EXPECT_EQ(result.items[1ul].outputs[0ul].templateName, "t1");
    EXPECT_EQ(result.items[1ul].outputs[0ul].outputPath, "item2.cpp");
    EXPECT_TRUE(result.items[1ul].data.empty());
}

TEST(InputTests, ParseData)
{
    // Arrange
    auto const context = MakeEmptyContext();
    auto const logger = MakeDebugLogger();

    auto input = std::istringstream(R"({
  "out": "out/files",
  "items":[
    {
      "name": "item1",
      "outputs": [
        {
          "template": "t1",
          "output":"out.cpp"
        }
      ],
      "data": {
        "something": "value1",
        "another": 42,
        "flag": true
      }
    }
  ]
})");

    // Act
    auto const result = LoadInput(std::move(input), context, logger);

    // Assert
    ASSERT_EQ(result.items.size(), 1ul);

    EXPECT_EQ(result.items[0ul].name, "item1");
    ASSERT_EQ(result.items[0ul].outputs.size(), 1ul);
    EXPECT_EQ(result.items[0ul].outputs[0ul].templateName, "t1");
    EXPECT_EQ(result.items[0ul].outputs[0ul].outputPath, "out.cpp");

    ASSERT_FALSE(result.items[0ul].data.empty());

    ASSERT_TRUE(result.items[0ul].data.contains("something"));
    ASSERT_TRUE(result.items[0ul].data["something"].is_string());
    EXPECT_EQ(result.items[0ul].data["something"].get<std::string>(), "value1");

    ASSERT_TRUE(result.items[0ul].data.contains("another"));
    ASSERT_TRUE(result.items[0ul].data["another"].is_number_integer());
    EXPECT_EQ(result.items[0ul].data["another"].get<int>(), 42);

    ASSERT_TRUE(result.items[0ul].data.contains("flag"));
    ASSERT_TRUE(result.items[0ul].data["flag"].is_boolean());
    EXPECT_EQ(result.items[0ul].data["flag"].get<bool>(), true);
}

}  // namespace ccg::tests
