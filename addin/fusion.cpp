#include "fusion.h"
#include "Core/Application/Application.h"                   // for Application
#include "Core/UserInterface/CommandCreatedEvent.h"         // for CommandCr...
#include "Core/UserInterface/CommandCreatedEventHandler.h"  // for CommandCr...
#include "Core/UserInterface/CommandDefinition.h"           // for CommandDefinition
#include "Core/UserInterface/CommandDefinitions.h"          // for CommandDefinitions
#include "Core/UserInterface/ToolbarControl.h"              // for ToolbarControl
#include "Core/UserInterface/ToolbarControls.h"             // for ToolbarControls
#include "Core/UserInterface/ToolbarPanel.h"                // for ToolbarPanel
#include "Core/UserInterface/ToolbarPanelList.h"            // for ToolbarPanelList
#include "Core/UserInterface/UserInterface.h"               // for UserInterface
#include "partgen/command.h"

namespace {
class CommandHandler : public adsk::core::CommandCreatedEventHandler {
 public:
  explicit CommandHandler(const std::shared_ptr<partgen::Command>& cmd) : cmd_(cmd) {}

  void notify(const adsk::core::Ptr<adsk::core::CommandCreatedEventArgs>& eventArgs) override { cmd_->execute(); }

 private:
  std::shared_ptr<partgen::Command> cmd_;
};
}  // namespace

Fusion::~Fusion() {
  auto ui = app_->userInterface();

  for (const auto& [id, panelId] : registeredCommands_) {
    auto cmd = ui->commandDefinitions()->itemById(id);
    if (cmd) cmd->deleteMe();

    auto panel = ui->allToolbarPanels()->itemById(panelId);
    if (panel) {
      auto control = panel->controls()->itemById(id);
      if (control) control->deleteMe();
    }
  }
}

void Fusion::messageBox(const std::string_view& message) const {
  app_->userInterface()->messageBox(static_cast<std::string>(message));
}

bool Fusion::registerCommand(const std::string_view& panel, const std::shared_ptr<partgen::Command>& cmd) {
  // keep a reference to the command and panel so we can remove them in the destructor
  registeredCommands_.emplace(cmd->id(), panel);

  auto ui = app_->userInterface();
  auto uiCmd = ui->commandDefinitions()->addButtonDefinition(cmd->id(), cmd->name(), cmd->description(),
                                                             cmd->resourceDirectory());

  if (!uiCmd) return false;

  uiCmd->commandCreated()->add(new CommandHandler(cmd));

  auto uiPanel = ui->allToolbarPanels()->itemById(static_cast<std::string>(panel));
  if (!uiPanel) return false;

  uiPanel->controls()->addCommand(uiCmd);
  return true;
}
