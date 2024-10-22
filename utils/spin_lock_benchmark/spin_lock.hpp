// From <Correctly implementing a spinlock in C++> by Rigtorp
// see: https://rigtorp.se/spinlock/

#pragma once

#include <atomic>

struct tas_lock
{
    std::atomic<bool> lock_ = {false};

    void lock()
    {
        while (lock_.exchange(true))
            ;
    }

    void unlock() { lock_.store(false); }
};

struct ttas_lock
{
    std::atomic<bool> lock_ = {false};
    void lock()
    {
        for (;;)
        {
            if (!lock_.exchange(true, std::memory_order_acquire))
            {
                break;
            }
            while (lock_.load(std::memory_order_relaxed))
            {
                __builtin_ia32_pause();
            }
        }
    }
    void unlock() { lock_.store(false, std::memory_order_release); }
};
