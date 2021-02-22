#include <memory>                              // for unique_ptr, make_shared
#include <string>                              // for basic_string, string
#include <string_view>                         // for string_view
#include "Core/Application/Application.h"      // for Application
#include "Core/Memory.h"                       // for Ptr
#include "Core/OSMacros.h"                     // for XI_EXPORT
#include "Core/UserInterface/UserInterface.h"  // for UserInterface
#include "partgen/addin.h"                     // for AddIn
#include "partgen/api.h"                       // for API

namespace {
std::unique_ptr<partgen::AddIn> addIn;

class Fusion : public partgen::API {
 public:
  explicit Fusion(adsk::core::Ptr<adsk::core::Application> app) : app_(app) {}

  void messageBox(const std::string_view& message) const override {
    app_->userInterface()->messageBox(static_cast<std::string>(message));
  }

 private:
  adsk::core::Ptr<adsk::core::Application> app_;
};
}  // namespace

extern "C" XI_EXPORT bool run(const char* context) {
  auto api = std::make_shared<Fusion>(adsk::core::Application::get());
  addIn = std::make_unique<partgen::AddIn>(api);

  return addIn->start();
}

extern "C" XI_EXPORT bool stop(const char* context) {
  auto result = addIn->stop();
  addIn = nullptr;
  return result;
}
