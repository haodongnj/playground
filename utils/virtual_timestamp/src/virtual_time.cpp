#include "virtual_time/virtual_time.hpp"

namespace virtual_time {

VirtualTime &VirtualTimeInstance(char const *const name, size_t size) {
  static VirtualTime virtual_time{name, size};
  return virtual_time;
}

} // namespace virtual_time