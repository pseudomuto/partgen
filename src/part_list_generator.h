#pragma once

#include <algorithm>       // for sort
#include <ostream>         // for ostream
#include <string>          // for string
#include <string_view>     // for string_view
#include <vector>          // for vector
#include "partgen/part.h"  // for Part

namespace partgen {
/**
 * Represents an ordered list of Part objects and their corresponding occurrence counts.
 */
class PartListGenerator {
 public:
  /**
   * Creates a new PartListGenerator.
   * @param parts the list of parts
   * @param units the units for the dimensions (cm, mm, inch, etc.)
   */
  PartListGenerator(const std::vector<Part>& parts, const std::string_view& units) : parts_(parts), units_(units) {
    // ensure parts are sorted correctly
    std::sort(parts_.begin(), parts_.end());
  }

  /**
   * @return a sorted list of parts
   */
  std::vector<Part> parts() const { return parts_; };

 private:
  std::vector<Part> parts_;
  std::string units_;
};
}  // namespace partgen

/**
 * Support writing to output streams.
 * @param out the output stream to write to
 * @param generator the generator containing the sorted parts list
 * @return a reference to the original output stream
 */
std::ostream& operator<<(std::ostream& out, const partgen::PartListGenerator& generator);
