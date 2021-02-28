#include "generate_command.h"
#include <memory>          // for shared_ptr
#include <type_traits>     // for remove_extent_t
#include <vector>          // for vector
#include "partgen/part.h"  // for Part

std::string partgen::GenerateCommand::id() const { return "partgen_gen_cmd"; }
std::string partgen::GenerateCommand::name() const { return "Generate Parts List"; }
std::string partgen::GenerateCommand::description() const { return "Generate a CSV of parts from component bodies"; }

void partgen::GenerateCommand::execute() const {
  for (const auto& part : api_->listParts()) {
    api_->messageBox(part.name());
  }
}
