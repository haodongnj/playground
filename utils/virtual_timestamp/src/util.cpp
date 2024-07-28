#include <chrono>
#include <iomanip>
#include <iostream>

namespace virtual_time {

void PrintDaytimeFromNanoseconds(int64_t nanoseconds) {
  // Define a duration in nanoseconds
  std::chrono::nanoseconds ns(nanoseconds);

  // Convert to system_clock::time_point
  std::chrono::system_clock::time_point tp(ns);

  // Convert to time_t (seconds since epoch)
  std::time_t time = std::chrono::system_clock::to_time_t(tp);

  // Convert to local time struct
  std::tm *localTime = std::localtime(&time);

  // Extract milliseconds for display
  int milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(ns % std::chrono::seconds(1)).count();

  // Output the formatted time
  std::cout << std::put_time(localTime, "%Y-%m-%d %H:%M:%S");
  std::cout << '.' << std::setfill('0') << std::setw(3) << milliseconds << std::endl;
}

} // namespace virtual_time
