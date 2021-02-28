#include "partgen/part.h"

bool partgen::Part::operator<(const partgen::Part& rhs) const {
  // ensure we sort by thickness DESC, name ASC
  auto myThickness = thickness();
  auto rhsThickness = rhs.thickness();

  if (myThickness != rhsThickness) {
    return myThickness > rhsThickness;
  }

  return name() < rhs.name();
}
