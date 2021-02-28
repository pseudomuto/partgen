#include <map>            // for map
#include <memory>         // for shared_ptr
#include <string>         // for string, basic_string
#include <string_view>    // for string_view
#include <vector>         // for vector
#include "Core/Memory.h"  // for Ptr
#include "partgen/api.h"  // for API
namespace adsk {
namespace core {
class Application;
}  // namespace core
}  // namespace adsk
namespace partgen {
class Command;
class Part;
}

class Fusion : public partgen::API {
 public:
  explicit Fusion(adsk::core::Ptr<adsk::core::Application> app) : app_(app) {}
  virtual ~Fusion();

  void messageBox(const std::string_view& message) const override;

  bool registerCommand(const std::string_view& panel, const std::shared_ptr<partgen::Command>& cmd) override;

  std::vector<partgen::Part> listParts() const override;

 private:
  adsk::core::Ptr<adsk::core::Application> app_;
  std::map<std::string, std::string> registeredCommands_;
};
