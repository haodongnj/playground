#include <iomanip>
#include <iostream>
#include <string>
#include <thread>

#include "virtual_time/util.hpp"
#include "virtual_time/virtual_time.hpp"

int main() {
  // an hour offset
  int64_t offset = 3600'000'000'000;
  int64_t timestamp = 1722159072523121402;
  virtual_time::VirtualTime().reset();

  for (int i = 0; i < 20; i++) {
    timestamp += offset;
    virtual_time::VirtualTimeInstance().push(timestamp);
    std::cout << "#" << i << " pushing timestamp: " << timestamp << std::endl;
    virtual_time::PrintDaytimeFromNanoseconds(timestamp);
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  return 0;
}
