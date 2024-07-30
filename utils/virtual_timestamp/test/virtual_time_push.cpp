#include <iomanip>
#include <iostream>
#include <string>
#include <thread>

#include "virtual_time/util.hpp"
#include "virtual_time/virtual_time.hpp"
#include <boost/timer/timer.hpp>

int main() {
  // an hour offset
  int64_t offset = 3600'000'000'000;
  int64_t timestamp = 1722159072523121402;
  virtual_time::VirtualTime().reset();

  const int range = 20'000;
  const int step = 1;
  int64_t total_time = 0;

  virtual_time::VirtualTimeInstance().reset();

  for (int i = 0; i < range; i += step) {
    timestamp += offset;
    {
      boost::timer::auto_cpu_timer t;
      virtual_time::VirtualTimeInstance().push(timestamp);
      total_time += t.elapsed().wall;
    }
    // virtual_time::PrintDaytimeFromNanoseconds(timestamp);
    std::this_thread::sleep_for(std::chrono::milliseconds(step));
  }

  std::cout << "Total time: " << total_time << " nanoseconds" << std::endl;
  std::cout << "Average time: " << total_time / (range / step) << " nanoseconds" << std::endl;

  return 0;
}
