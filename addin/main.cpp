#include <memory>                          // for unique_ptr, make_shared
#include "Core/Application/Application.h"  // for Application
#include "Core/OSMacros.h"                 // for XI_EXPORT
#include "fusion.h"                        // for Fusion
#include "partgen/addin.h"                 // for AddIn

namespace {
std::unique_ptr<partgen::AddIn> addIn;
}

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
