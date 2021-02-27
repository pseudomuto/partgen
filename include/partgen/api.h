#pragma once

#include <string_view>
namespace partgen {
class Command;
}

namespace partgen {
/**
 * An abstract class that acts as a facade for the Fusion 360 APIs. Having this
 * class in place allows me to separate the simple logic of this addin from the
 * complexities of Fusion 360.
 */
class API {
 public:
  virtual ~API() {}
  /**
   * Sends the supplied message to ui->messageBox.
   * @param message the message to show
   */
  virtual void messageBox(const std::string_view& message) const = 0;

  /**
   * Adds the supplied command to the name panel.
   * @param panel the id of the panel to add the command to (e.g. SolidScriptsAddinsPanel)
   * @param cmd the command to add
   * @return whether or not the command was added
   */
  virtual bool registerCommand(const std::string_view& panel, const std::shared_ptr<Command>& cmd) = 0;
};
}  // namespace partgen
