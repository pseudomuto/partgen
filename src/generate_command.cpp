#include "generate_command.h"
#include <memory>                 // for shared_ptr
#include <fstream>                // for ofstream
#include <type_traits>            // for remove_extent_t
#include "part_list_generator.h"  // for operator<<, PartListGenerator

std::string partgen::GenerateCommand::id() const { return "partgen_gen_cmd"; }
std::string partgen::GenerateCommand::name() const { return "Generate Parts List"; }
std::string partgen::GenerateCommand::description() const { return "Generate a CSV of parts from component bodies"; }

void partgen::GenerateCommand::execute() const {
  auto filename = api_->selectOutputFile();
  if (filename == "") return;

  auto generator = partgen::PartListGenerator(api_);
  auto file = std::ofstream(filename);
  file << "Length,Width,Qty,Material,Label" << std::endl;
  file << generator;
  file.flush();
  file.close();
}
