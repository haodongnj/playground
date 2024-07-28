#include <iomanip>
#include <iostream>
#include <string>
#include <thread>

#include "virtual_time/util.hpp"
#include "virtual_time/virtual_time.hpp"

int main() {
  // an hour offset
  int64_t offset = 3600'000'000'000;
  int64_t timestamp;
  for (int i = 0; i < 20; i++) {
    timestamp =
        std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch())
            .count();
    timestamp += offset;
    virtual_time::push_virtual_timestamp(timestamp);
    std::cout << "Pushed timestamp: " << timestamp << std::endl;
    printDaytimeFromNanoseconds(timestamp);
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  return 0;
}
