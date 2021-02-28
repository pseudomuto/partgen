#include "partgen/addin.h"
#include <type_traits>         // for remove_extent_t
#include "generate_command.h"  // for GenerateCommand

namespace {
constexpr auto kPanelId = "SolidScriptsAddinsPanel";
}

bool partgen::AddIn::start() {
  auto cmd = std::make_shared<GenerateCommand>(api_);
  return api_->registerCommand(kPanelId, cmd);
}

bool partgen::AddIn::stop() { return true; }
