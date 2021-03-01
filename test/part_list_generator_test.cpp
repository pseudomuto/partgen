#include <gtest/gtest.h>          // for Test, SuiteApiResolver, TestInfo (p...
#include <sstream>                // for basic_stringstream, stringstream
#include <vector>                 // for vector
#include "part_list_generator.h"  // for PartListGenerator
#include "partgen/part.h"         // for Part

TEST(PartListGenerator, GeneratesAnOrderedSetOfPartsAndQuantities) {
  auto generator = partgen::PartListGenerator(std::vector<partgen::Part>{
    partgen::Part("A", 0, 0, 1.2),
    partgen::Part("A", 0, 0, 1.2),
    partgen::Part("E", 0, 0, 0.6),
    partgen::Part("B", 0, 0, 0.6),
    partgen::Part("B", 0, 0, 0.6),
    partgen::Part("B", 0, 0, 0.6),
    partgen::Part("C", 0, 0, 1.8),
    partgen::Part("D", 0, 0, 1.8),
    partgen::Part("E", 0, 0, 0.6)
  }, "cm");

  auto expected =
    "C,1,0cm,0cm,1.8cm\n"
    "D,1,0cm,0cm,1.8cm\n"
    "A,2,0cm,0cm,1.2cm\n"
    "B,3,0cm,0cm,0.6cm\n"
    "E,2,0cm,0cm,0.6cm\n";

  auto str = std::stringstream{};
  str << generator;

  ASSERT_EQ(expected, str.str());
}

TEST(PartListGenerator, WhenNoPartsSupplied) {
  auto generator = partgen::PartListGenerator(std::vector<partgen::Part>{}, "cm");
  auto str = std::stringstream{};
  str << generator;

  ASSERT_EQ("", str.str());
}
