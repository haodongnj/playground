#include <sys/time.h>

#include "virtual_time/virtual_time.hpp"

int gettimeofday(struct timeval *tv, struct timezone *tz) {
  int64_t ns;
  virtual_time::VirtualTimeInstance().get(ns);
  tv->tv_sec = (ns / 1000'000'000);
  tv->tv_usec = (ns % 1000'000'000);
  return 0;
}

int clock_gettime(clockid_t clk_id, struct timespec *tp) {
  int64_t ns;
  virtual_time::VirtualTimeInstance().get(ns);
  tp->tv_sec = (ns / 1000'000'000);
  tp->tv_nsec = (ns % 1000'000'000);
  return 0;
}
