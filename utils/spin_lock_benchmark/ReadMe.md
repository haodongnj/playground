
# Spin Lock Benchmark

参照[Correctly implementing a spinlock in C++](https://rigtorp.se/spinlock/)来测试TAS自旋锁和经过优化的TTAS自旋锁的性能。

编译：
```bash
# For TTAS:
g++ benchmark.cpp -lpthread -DTTAS
# For TAS:
g++ benchmark.cpp -lpthread
```

Use perf-stat to measure the number of cache misses:

```bash
sudo perf stat -e L1-dcache-loads,L1-dcache-load-misses ./a.out
```

在我的机器上测试，也能看出TTAS相比TAS有更少的cache miss。

CPU配置：
```bash
Architecture:                         x86_64
CPU op-mode(s):                       32-bit, 64-bit
Byte Order:                           Little Endian
Address sizes:                        48 bits physical, 48 bits virtual
CPU(s):                               24
On-line CPU(s) list:                  0-23
Thread(s) per core:                   2
Core(s) per socket:                   12
Socket(s):                            1
NUMA node(s):                         1
Vendor ID:                            AuthenticAMD
CPU family:                           25
Model:                                33
Model name:                           AMD Ryzen 9 5900X 12-Core Processor
Stepping:                             0
Frequency boost:                      enabled
CPU MHz:                              2200.000
CPU max MHz:                          4200.0000
CPU min MHz:                          2200.0000
BogoMIPS:                             8400.48
Virtualization:                       AMD-V
L1d cache:                            384 KiB
L1i cache:                            384 KiB
L2 cache:                             6 MiB
L3 cache:                             64 MiB
```

TAS:
```bash
 Performance counter stats for './a.out':

    48,635,800,052      L1-dcache-loads                                             
     4,526,421,316      L1-dcache-load-misses     #    9.31% of all L1-dcache accesses

      64.901401553 seconds time elapsed

    1549.340657000 seconds user
       0.027986000 seconds sys
```

TTAS:
```bash
 Performance counter stats for './a.out':

   594,455,105,879      L1-dcache-loads                                             
     2,298,942,812      L1-dcache-load-misses     #    0.39% of all L1-dcache accesses

      56.481409167 seconds time elapsed

    1347.286257000 seconds user
       0.019986000 seconds sys
```
