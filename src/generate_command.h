#pragma once

#include <string>             // for string
#include "partgen/command.h"  // for Command

namespace partgen {
class GenerateCommand : public Command {
 public:
  using Command::Command;

  std::string id() const override;
  std::string name() const override;
  std::string description() const override;

  void execute() const override;
};
}  // namespace partgen
