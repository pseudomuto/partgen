#pragma once

#include <string_view>

namespace partgen {
/**
 * An abstract class that acts as a facade for the Fusion 360 APIs. Having this
 * class in place allows me to separate the logic of this addin from the
 * complexities of Fusion 360.
 */
class API {
 public:
  /**
   * Sends the supplied message to ui->messageBox.
   * @param message the message to show
   */
  virtual void messageBox(const std::string_view& message) const = 0;
};
}  // namespace partgen
