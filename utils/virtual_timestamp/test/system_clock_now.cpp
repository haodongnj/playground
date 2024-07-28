#include "virtual_time/util.hpp"
#include <chrono>
#include <iostream>
#include <thread>

int main() {
  int64_t timestamp;
  for (int i = 0; i < 20; i++) {
    timestamp =
        std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch())
            .count();
    std::cout << "#" << i << " got timestamp: " << timestamp << std::endl;
    virtual_time::PrintDaytimeFromNanoseconds(timestamp);
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}