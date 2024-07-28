#include <chrono>
#include <iostream>
#include <thread>

int main() {
  int64_t timestamp;
  for (int i = 0; i < 20; i++) {
    timestamp =
        std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch())
            .count();
    std::cout << "Got timestamp: " << timestamp << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}