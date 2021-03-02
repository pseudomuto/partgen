#include "generate_command.h"
#include <gmock/gmock-actions.h>        // for Return, ImplicitCast_, Return...
#include <gmock/gmock-spec-builders.h>  // for EXPECT_CALL, MockSpec, TypedE...
#include <gtest/gtest.h>                // for Test, AssertionResult, Message
#include <functional>                   // for __base
#include <sstream>                      // for stringstream
#include <vector>                       // for vector
#include "mocks/api.h"                  // for API
#include "part_list_generator.h"        // for PartListGenerator
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
  EXPECT_CALL(*api, listParts).WillOnce(Return(parts));
  EXPECT_CALL(*api, measurement)
      .WillOnce(Return("1cm"))
      .WillOnce(Return("2cm"))
      .WillOnce(Return("1.2cm"))
      .WillOnce(Return("3cm"))
      .WillOnce(Return("4cm"))
      .WillOnce(Return("0.6cm"));

  EXPECT_CALL(*api, messageBox);

  auto cmd = partgen::GenerateCommand(api);
  cmd.execute();
}
