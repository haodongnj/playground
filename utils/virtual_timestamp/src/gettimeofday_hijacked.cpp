#define _GNU_SOURCE
#include "virtual_time/gettimeofday_hijacked.h"
#include "virtual_time/virtual_time.hpp"
#include <errno.h>
#include <sys/time.h>

int gettimeofday(struct timeval *tv, void *tz) {
  int64_t timestamp;
  virtual_time::get_virtual_timestamp(timestamp);
  tv->tv_sec = timestamp / 1000000;
  tv->tv_usec = timestamp % 1000000;
  return 0;
}

int settimeofday(const struct timeval *tv, const struct timezone *tz) {
  int64_t timestamp = tv->tv_sec * 1000000 + tv->tv_usec;
  virtual_time::push_virtual_timestamp(timestamp);
  return 0;
}
