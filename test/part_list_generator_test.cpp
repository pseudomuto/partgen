#include "part_list_generator.h"
#include <gmock/gmock-actions.h>        // for Return, ReturnAction, Implici...
#include <gmock/gmock-spec-builders.h>  // for EXPECT_CALL, MockSpec, TypedE...
#include <gtest/gtest.h>                // for Test, ElemFromListImpl<>::type
#include <functional>                   // for __base
#include <sstream>                      // for basic_stringstream
#include <string>                       // for string, basic_string
#include <vector>                       // for vector
#include "mocks/api.h"                  // for API
#include "partgen/part.h"               // for Part

TEST(PartListGenerator, GeneratesAnOrderedSetOfPartsAndQuantities) {
  using ::testing::Return;

  auto parts = std::vector<partgen::Part>{
      partgen::Part("A", 0, 0, 1.2), partgen::Part("A", 0, 0, 1.2), partgen::Part("E", 0, 0, 0.6),
      partgen::Part("B", 0, 0, 0.6), partgen::Part("B", 0, 0, 0.6), partgen::Part("B", 0, 0, 0.6),
      partgen::Part("C", 0, 0, 1.8), partgen::Part("D", 0, 0, 1.8), partgen::Part("E", 0, 0, 0.6)};

  auto api = std::make_shared<mocks::API>();
  EXPECT_CALL(*api, listParts).WillOnce(Return(parts));
  EXPECT_CALL(*api, measurement(0.0)).WillRepeatedly(Return("0mm"));
  EXPECT_CALL(*api, measurement(0.6)).WillRepeatedly(Return("6mm"));
  EXPECT_CALL(*api, measurement(1.2)).WillRepeatedly(Return("12mm"));
  EXPECT_CALL(*api, measurement(1.8)).WillRepeatedly(Return("18mm"));

  auto generator = partgen::PartListGenerator(api);

  auto expected =
      "C,1,0mm,0mm,18mm\n"
      "D,1,0mm,0mm,18mm\n"
      "A,2,0mm,0mm,12mm\n"
      "B,3,0mm,0mm,6mm\n"
      "E,2,0mm,0mm,6mm\n";

  auto str = std::stringstream{};
  str << generator;

  ASSERT_EQ(expected, str.str());
}

TEST(PartListGenerator, WhenNoPartsSupplied) {
  auto api = std::make_shared<mocks::API>();
  EXPECT_CALL(*api, listParts).WillOnce(::testing::Return(std::vector<partgen::Part>{}));

  auto generator = partgen::PartListGenerator(api);
  auto str = std::stringstream{};
  str << generator;

  ASSERT_EQ("", str.str());
}
