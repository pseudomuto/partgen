#include "partgen/addin.h"
#include "partgen/api.h"

bool partgen::AddIn::start() {
  api_->messageBox("loaded");
  return true;
}

bool partgen::AddIn::stop() { return true; }
