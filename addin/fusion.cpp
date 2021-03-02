#include "fusion.h"
#include <algorithm>                                        // for remove_if
#include <functional>                                       // for greater
#include <iterator>                                         // for back_inse...
#include <sstream>                                          // for stringstream
#include <type_traits>                                      // for remove_ex...
#include "Core/Application/Application.h"                   // for Application
#include "Core/Application/Document.h"                      // for Document
#include "Core/Application/Product.h"                       // for Product
#include "Core/Geometry/BoundingBox3D.h"                    // for BoundingBox3D
#include "Core/Geometry/Point3D.h"                          // for Point3D
#include "Core/UserInterface/CommandCreatedEvent.h"         // for CommandCr...
#include "Core/UserInterface/CommandCreatedEventHandler.h"  // for CommandCr...
#include "Core/UserInterface/CommandDefinition.h"           // for CommandDe...
#include "Core/UserInterface/CommandDefinitions.h"          // for CommandDe...
#include "Core/UserInterface/FileDialog.h"                  // for FileDialog
#include "Core/UserInterface/ToolbarControl.h"              // for ToolbarCo...
#include "Core/UserInterface/ToolbarControls.h"             // for ToolbarCo...
#include "Core/UserInterface/ToolbarPanel.h"                // for ToolbarPanel
#include "Core/UserInterface/ToolbarPanelList.h"            // for ToolbarPa...
#include "Core/UserInterface/UserInterface.h"               // for UserInter...
#include "Fusion/BRep/BRepBodies.h"                         // for BRepBodies
#include "Fusion/BRep/BRepBody.h"                           // for BRepBody
#include "Fusion/Components/Component.h"                    // for Component
#include "Fusion/Components/Occurrence.h"                   // for Occurrence
#include "Fusion/Components/OccurrenceList.h"               // for OccurrenceList
#include "Fusion/Fusion/Design.h"                           // for Design
#include "Fusion/Fusion/FusionUnitsManager.h"               // for FusionUnitsManager
#include "partgen/command.h"                                // for Command
#include "partgen/part.h"                                   // for Part
namespace adsk {
namespace core {
class CommandCreatedEventArgs;
}
}  // namespace adsk

namespace {
class CommandHandler : public adsk::core::CommandCreatedEventHandler {
 public:
  explicit CommandHandler(const std::shared_ptr<partgen::Command>& cmd) : cmd_(cmd) {}

  void notify(const adsk::core::Ptr<adsk::core::CommandCreatedEventArgs>& eventArgs) override { cmd_->execute(); }

 private:
  std::shared_ptr<partgen::Command> cmd_;
};

partgen::Part toPart(const adsk::core::Ptr<adsk::fusion::BRepBody>& body) {
  auto um = body->parentComponent()->parentDesign()->fusionUnitsManager();
  auto box = body->boundingBox();
  auto min = box->minPoint();
  auto max = box->maxPoint();

  // HACK: not sure what to do here. For now, length >= width >= thickness is the heuristic.
  auto dimensions = std::vector{max->x() - min->x(), max->y() - min->y(), max->z() - min->z()};
  std::sort(dimensions.begin(), dimensions.end(), std::greater<double>{});

  return partgen::Part(body->parentComponent()->partNumber() + "." + body->name(), dimensions[0], dimensions[1],
                       dimensions[2]);
}
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

std::vector<partgen::Part> Fusion::listParts() const {
  auto design = app_->activeProduct()->cast<adsk::fusion::Design>();
  auto occurrences = design->rootComponent()->allOccurrences();
  auto components = std::vector<adsk::core::Ptr<adsk::fusion::Component>>{};

  auto toComponent = [](const adsk::core::Ptr<adsk::fusion::Occurrence>& occ) { return occ->component(); };
  auto bodyLess = [](const adsk::core::Ptr<adsk::fusion::Component>& comp) { return comp->bRepBodies()->count() == 0; };

  // get all components that have bodies
  std::transform(occurrences.begin(), occurrences.end(), std::back_inserter(components), toComponent);
  components.erase(std::remove_if(components.begin(), components.end(), bodyLess), components.end());

  auto parts = std::vector<partgen::Part>{};
  parts.reserve(components.size() * 1.1);  // assuming most components have a single body

  for (const auto& comp : components) {
    for (const auto& body : comp->bRepBodies()) {
      parts.push_back(toPart(body));
    }
  }

  return parts;
}

std::string Fusion::measurement(double centimetres) const {
  auto um = app_->activeProduct()->cast<adsk::fusion::Design>()->fusionUnitsManager();
  auto units = um->defaultLengthUnits();
  auto stream = std::stringstream{};
  stream << um->convert(centimetres, "cm", units) << units;

  return stream.str();
}

std::string Fusion::selectOutputFile() const {
  auto dlg = app_->userInterface()->createFileDialog();
  dlg->filter("CSV (*.csv)");
  dlg->filterIndex(0);
  dlg->isMultiSelectEnabled(false);
  dlg->initialFilename(app_->activeProduct()->parentDocument()->name() + ".csv");
  dlg->title("Save Parts List");
  if (dlg->showSave() != adsk::core::DialogOK) return "";

  return dlg->filename();
}
