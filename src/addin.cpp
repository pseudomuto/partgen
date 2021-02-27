#include "partgen/addin.h"
#include "generate_command.h"
#include "partgen/api.h"

namespace {
constexpr auto kPanelId = "SolidScriptsAddinsPanel";
}

bool partgen::AddIn::start() {
  auto cmd = std::make_shared<GenerateCommand>(api_);
  return api_->registerCommand(kPanelId, cmd);
}

bool partgen::AddIn::stop() { return true; }
