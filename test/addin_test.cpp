#include "partgen/addin.h"              // for AddIn
#include <gmock/gmock-spec-builders.h>  // for EXPECT_CALL, MockSpec
#include <gtest/gtest.h>                // for Test, AssertionResult, SuiteA...
#include <memory>                       // for shared_ptr
#include "mocks/api.h"                  // for API

TEST(AddIn, StartNotifiesAboutLoading) {
  auto api = std::make_shared<mocks::API>();
  EXPECT_CALL(*api, messageBox);

  auto addin = partgen::AddIn(api);
  ASSERT_TRUE(addin.start());
}

TEST(AddIn, StopReturnsTrue) {
  auto addin = partgen::AddIn(nullptr);
  ASSERT_TRUE(addin.stop());
}
