#include "part_list_generator.h"
#include <string>          // for operator==, string
#include "partgen/part.h"  // for Part

namespace {
void write(std::ostream& out, const partgen::Part& part, int qty) {
  out << part.name() << ",";
  out << qty << ",";
  out << part.length() << "cm,";
  out << part.width() << "cm,";
  out << part.thickness() << "cm";
  out << std::endl;
}
}  // namespace

std::ostream& operator<<(std::ostream& out, const partgen::PartListGenerator& generator) {
  auto parts = generator.parts();
  if (parts.size() == 0) return out;

  auto quantity = 0;
  for (auto i = 0; i < parts.size(); ++i) {
    quantity++;

    if (i == parts.size() - 1) {
      write(out, parts[i], quantity);
      break;
    }

    if (parts[i+1].name() == parts[i].name()) continue;

    write(out, parts[i], quantity);
    quantity = 0;
  }

  return out;
}
