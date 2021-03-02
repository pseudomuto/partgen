#include "part_list_generator.h"
#include <algorithm>       // for sort
#include <string>          // for char_traits, operator==, string
#include <type_traits>     // for remove_extent_t
#include <vector>          // for vector
#include "partgen/part.h"  // for Part
namespace partgen {
class API;
}

namespace {
void write(const std::shared_ptr<partgen::API>& api, std::ostream& out, const partgen::Part& part, int qty) {
  out << part.name() << ",";
  out << qty << ",";
  out << api->measurement(part.length()) << ",";
  out << api->measurement(part.width()) << ",";
  out << api->measurement(part.thickness()) << std::endl;
}
}  // namespace

std::ostream& partgen::operator<<(std::ostream& out, const partgen::PartListGenerator& generator) {
  auto parts = generator.api_->listParts();
  if (parts.size() == 0) return out;

  std::sort(parts.begin(), parts.end());

  auto quantity = 0;
  for (auto i = 0; i < parts.size(); ++i) {
    quantity++;

    if (i == parts.size() - 1) {
      write(generator.api_, out, parts[i], quantity);
      break;
    }

    if (parts[i + 1].name() == parts[i].name()) continue;

    write(generator.api_, out, parts[i], quantity);
    quantity = 0;
  }

  return out;
}
