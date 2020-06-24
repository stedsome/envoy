#include "test/test_common/global.h"

#include "common/common/assert.h"

namespace Envoy {
namespace Test {

Globals& Globals::instance() {
  static Globals* globals = new Globals;
  return *globals;
}

std::string Globals::describeActiveSingletonsHelper() {
  std::string ret;
  Thread::ReleasableLockGuard map_lock(map_mutex_);
  for (auto& [name, singleton] : singleton_map_) {
    SingletonSharedPtr singleton_ptr = singleton.lock();
    if (singleton_ptr != nullptr) {
      absl::StrAppend(&ret, "Unexpected active singleton: ", name, "\n");
    }
  }
  return ret;
}

} // namespace Test
} // namespace Envoy
