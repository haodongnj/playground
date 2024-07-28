#include <chrono>
#include <iomanip>
#include <iostream>

void printDaytimeFromNanoseconds(int64_t nanoseconds) {
  // Convert nanoseconds to seconds using std::chrono
  auto ns = std::chrono::nanoseconds(nanoseconds);
  auto secs = std::chrono::duration_cast<std::chrono::seconds>(ns);
  auto hrs = std::chrono::duration_cast<std::chrono::hours>(secs);
  auto mins = std::chrono::duration_cast<std::chrono::minutes>(secs % std::chrono::hours(1));
  auto secs_remainder = secs % std::chrono::minutes(1);
  auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(ns % std::chrono::seconds(1));
  auto micros = std::chrono::duration_cast<std::chrono::microseconds>(ns % std::chrono::milliseconds(1));
  auto nanos = ns % std::chrono::microseconds(1);

  // Output the result
  std::cout << std::setfill('0') << std::setw(2) << hrs.count() << ":" << std::setw(2) << mins.count() << ":"
            << std::setw(2) << secs_remainder.count() << "." << std::setw(3) << millis.count() << " " << std::setw(3)
            << micros.count() << " " << std::setw(3) << nanos.count() << std::endl;
}