#include <thread>
#include <vector>
#include "spin_lock.hpp"

#ifndef TTAS

tas_lock lock;

void benchmark_tas_lock(int n)
{
    for (int i = 0; i < n; ++i)
    {
        lock.lock();
        lock.unlock();
    }
}

#else
ttas_lock lock2;

void benchmark_ttas_lock(int n)
{
    for (int i = 0; i < n; ++i)
    {
        lock2.lock();
        lock2.unlock();
    }
}
#endif

int main()
{
    constexpr int num_threads = 64;
    constexpr int num_iterations = 1000000;
    std::vector<std::thread> threads;
    threads.reserve(num_threads);

#ifndef TTAS
    for (int i = 0; i < num_threads; ++i)
    {
        threads.emplace_back(benchmark_tas_lock, num_iterations);
    }

#else
    for (int i = 0; i < num_threads; ++i)
    {
        threads.emplace_back(benchmark_ttas_lock, num_iterations);
    }
#endif
    for (auto &t : threads)
    {
        t.join();
    }
    return 0;
}