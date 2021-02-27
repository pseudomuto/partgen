#pragma once

#include <gmock/gmock.h>
#include <memory>
#include "partgen/api.h"

namespace mocks {
class API : public partgen::API, std::enable_shared_from_this<API> {
 public:
  std::shared_ptr<API> getptr() { return shared_from_this(); }

  MOCK_METHOD(void, messageBox, (const std::string_view&), (const, override));
  MOCK_METHOD(bool, registerCommand, (const std::string_view&, const std::shared_ptr<partgen::Command>&), (override));
};
}  // namespace mocks
