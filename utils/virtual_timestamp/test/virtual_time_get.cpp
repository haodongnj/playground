#include <iostream>
#include <thread>

#include "boost/timer/timer.hpp"
#include "virtual_time/util.hpp"
#include "virtual_time/virtual_time.hpp"

int main() {
  int64_t timestamp;
  int64_t total_time = 0;

  const int step = 1;
  const int range = 20'000;
  for (int i = 0; i < range; i += step) {
    {
      boost::timer::auto_cpu_timer t;
      virtual_time::VirtualTimeInstance().get(timestamp);
      total_time += t.elapsed().wall;
    }
    if (timestamp < 0) {
      continue;
    } else {
      // virtual_time::PrintDaytimeFromNanoseconds(timestamp);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(step));
  }

  std::cout << "Total time to get timestamp: " << total_time << " ns" << std::endl;
  std::cout << "Average time to get timestamp: " << total_time / (range / step) << " ns" << std::endl;
}
