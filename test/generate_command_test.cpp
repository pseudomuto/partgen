#include "generate_command.h"
#include <gmock/gmock-actions.h>        // for Return, ReturnAction, Implici...
#include <gmock/gmock-matchers.h>       // for Eq
#include <gmock/gmock-spec-builders.h>  // for TypedExpectation, EXPECT_CALL
#include <gtest/gtest.h>                // for Test, AssertionResult, Message
#include <functional>                   // for __base
#include <vector>                       // for vector
#include "mocks/api.h"                  // for API
#include "partgen/part.h"               // for Part

TEST(GenerateCommand, DefinesMetadata) {
  auto api = std::make_shared<mocks::API>();
  auto cmd = partgen::GenerateCommand(api);

  ASSERT_FALSE(cmd.id().empty());
  ASSERT_FALSE(cmd.name().empty());
  ASSERT_FALSE(cmd.description().empty());
  ASSERT_EQ("resources", cmd.resourceDirectory());
}

TEST(GenerateCommand, ExecuteGetsPartsListFromAPI) {
  using ::testing::Eq;
  using ::testing::Return;

  auto parts = std::vector<partgen::Part>{partgen::Part("A", 1, 2, 1.2), partgen::Part("B", 3, 4, 0.6)};

  auto api = std::make_shared<mocks::API>();
  EXPECT_CALL(*api, selectOutputFile).WillOnce(Return("/tmp/parts.csv"));
  EXPECT_CALL(*api, listParts).WillOnce(Return(parts));
  EXPECT_CALL(*api, measurement)
      .WillOnce(Return("1cm"))
      .WillOnce(Return("2cm"))
      .WillOnce(Return("1.2cm"))
      .WillOnce(Return("3cm"))
      .WillOnce(Return("4cm"))
      .WillOnce(Return("0.6cm"));

  auto cmd = partgen::GenerateCommand(api);
  cmd.execute();
}

TEST(GenerateCommand, ExecuteBailsWhenNotFileSelected) {
  using ::testing::Return;

  auto api = std::make_shared<mocks::API>();
  EXPECT_CALL(*api, selectOutputFile).WillOnce(Return(""));
  // No other calls made

  auto cmd = partgen::GenerateCommand(api);
  cmd.execute();
}
