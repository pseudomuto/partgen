#include "partgen/addin.h"
#include <gmock/gmock-actions.h>        // for Return, ReturnAction, ReturnA...
#include <gmock/gmock-spec-builders.h>  // for ImplicitCast_, EXPECT_CALL
#include <gtest/gtest.h>                // for Test, AssertionResult, SuiteA...
#include <functional>                   // for __base
#include <memory>                       // for make_shared, shared_ptr
#include "mocks/api.h"                  // for API

TEST(AddIn, Start) {
  auto api = std::make_shared<mocks::API>();
  EXPECT_CALL(*api, registerCommand).WillOnce(::testing::Return(true));

  auto addin = partgen::AddIn(api);
  ASSERT_TRUE(addin.start());
}

TEST(AddIn, StartWhenCommandRegistrationFails) {
  auto api = std::make_shared<mocks::API>();
  EXPECT_CALL(*api, registerCommand).WillOnce(::testing::Return(false));

  auto addin = partgen::AddIn(api);
  ASSERT_FALSE(addin.start());
}

TEST(AddIn, StopReturnsTrue) {
  auto addin = partgen::AddIn(nullptr);
  ASSERT_TRUE(addin.stop());
}
