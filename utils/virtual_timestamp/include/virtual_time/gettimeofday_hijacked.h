#include <sys/time.h>

int gettimeofday(struct timeval *tv, void *tz);
int settimeofday(const struct timeval *tv, const struct timezone *tz);