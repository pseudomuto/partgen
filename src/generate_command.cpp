#include "generate_command.h"

std::string partgen::GenerateCommand::id() const { return "partgen_gen_cmd"; }
std::string partgen::GenerateCommand::name() const { return "Generate Parts List"; }
std::string partgen::GenerateCommand::description() const { return "Generate a CSV of parts from component bodies"; }

void partgen::GenerateCommand::execute() const { api_->messageBox("Clicked"); }
