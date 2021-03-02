#pragma once

#include <memory>         // for shared_ptr
#include <ostream>        // for ostream
#include "partgen/api.h"  // for API

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
  PartListGenerator(const std::shared_ptr<API>& api) : api_(api) {}

  /**
   * Support writing to output streams.
   * @param out the output stream to write to
   * @param generator the generator containing the sorted parts list
   * @return a reference to the original output stream
   */
  friend std::ostream& operator<<(std::ostream& out, const PartListGenerator& generator);

 private:
  std::shared_ptr<API> api_;
};
}  // namespace partgen
