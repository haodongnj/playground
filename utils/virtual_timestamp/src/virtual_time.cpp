#include "virtual_time/virtual_time.hpp"

namespace virtual_time {

void push_virtual_timestamp(int64_t timestamp, char const *const name, size_t size) {
  static VirtualTime virtual_time{name, size};
  virtual_time.push(timestamp);
}

void get_virtual_timestamp(int64_t &timestamp, char const *const name, size_t size) {
  static VirtualTime virtual_time{name, size};
  virtual_time.get(timestamp);
}

} // namespace virtual_time