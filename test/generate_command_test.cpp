#include "generate_command.h"
#include "mocks/api.h"
#include <gmock/gmock-spec-builders.h>  // for EXPECT_CALL, MockSpec
#include <gtest/gtest.h>

TEST(GenerateCommand, DefinesMetadata) {
  auto api = std::make_shared<mocks::API>();
  auto cmd = partgen::GenerateCommand(api);

  ASSERT_FALSE(cmd.id().empty());
  ASSERT_FALSE(cmd.name().empty());
  ASSERT_FALSE(cmd.description().empty());
  ASSERT_EQ("resources", cmd.resourceDirectory());
}

TEST(GenerateCommand, ExecuteCallsAPI) {
  auto api = std::make_shared<mocks::API>();
  EXPECT_CALL(*api, messageBox);

  auto cmd = partgen::GenerateCommand(api);
  cmd.execute();
}
