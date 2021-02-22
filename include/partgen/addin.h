#pragma once

#include <memory>  // for shared_ptr
namespace partgen {
class API;
}

namespace partgen {
/**
 * The main entry point into the add in.
 */
class AddIn {
 public:
  explicit AddIn(const std::shared_ptr<API>& api) : api_(api) {}

  /**
   * Starts the add-in.
   * @return false if the add-in failed to start
   */
  bool start();

  /**
   * Stops the add-in, cleaning up any resources.
   * @return false if the cleanup fails
   */
  bool stop();

 private:
  std::shared_ptr<API> api_;
};
}  // namespace partgen
