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
  auto parts = std::vector<partgen::Part>{partgen::Part("A", 1, 2, 1.2), partgen::Part("B", 3, 4, 0.6)};

  auto stream = std::stringstream{};
  stream << partgen::PartListGenerator(parts, "cm");

  auto api = std::make_shared<mocks::API>();
  EXPECT_CALL(*api, listParts).WillOnce(::testing::Return(parts));
  EXPECT_CALL(*api, messageBox(::testing::Eq(stream.str())));

  auto cmd = partgen::GenerateCommand(api);
  cmd.execute();
}
