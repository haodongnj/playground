#include <iostream>
#include <thread>

#include "virtual_time/util.hpp"
#include "virtual_time/virtual_time.hpp"

int main() {
  int64_t timestamp;
  for (int i = 0; i < 20; i++) {
    virtual_time::get_virtual_timestamp(timestamp);
    std::cout << "Got timestamp: " << timestamp << std::endl;
    if (timestamp < 0) {
      std::cout << "No timestamp available" << std::endl;
    } else {
      printDaytimeFromNanoseconds(timestamp);
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}
