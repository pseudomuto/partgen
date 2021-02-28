#include "partgen/part.h"
#include <gtest/gtest.h>  // for Test, ASSERT_EQ, Message, TestPartResult
#include <algorithm>      // for sort
#include <vector>         // for vector

TEST(Part, SortsByThicknessDESCNameASC) {
  auto parts = std::vector<partgen::Part>{
    partgen::Part("A", 0, 0, 1.2),
    partgen::Part("E", 0, 0, 0.6),
    partgen::Part("B", 0, 0, 0.6),
    partgen::Part("C", 0, 0, 1.8),
    partgen::Part("D", 0, 0, 1.8)
  };

  std::sort(parts.begin(), parts.end());
  ASSERT_EQ("C", parts[0].name());
  ASSERT_EQ("D", parts[1].name());
  ASSERT_EQ("A", parts[2].name());
  ASSERT_EQ("B", parts[3].name());
  ASSERT_EQ("E", parts[4].name());
}
