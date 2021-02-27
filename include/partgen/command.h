#pragma once

#include "api.h"
#include <string>

namespace partgen {
/**
 * An abstract class representing a UI command.
 */
class Command {
 public:
   explicit Command(const std::shared_ptr<API>& api) : api_(api) {}

  /** @return the unique id for this command */
  virtual std::string id() const = 0;
  /** @return the name/label for this command */
  virtual std::string name() const = 0;
  /** @return a description of the command */
  virtual std::string description() const = 0;
  /** @return the directory that contains resources (images) for rendering */
  virtual std::string resourceDirectory() const { return "resources"; }

  /**
   * Actually execute the command. This will be called whenever the UI command is clicked.
   */
  virtual void execute() const = 0;

 protected:
  std::shared_ptr<API> api_;
};
}  // namespace partgen
