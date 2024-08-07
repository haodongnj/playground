#pragma once

#include <atomic>
#include <boost/interprocess/containers/deque.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <iostream>

namespace virtual_time {

using ShmemAllocator =
    boost::interprocess::allocator<int64_t, boost::interprocess::managed_shared_memory::segment_manager>;
using ipc_deque = boost::interprocess::deque<int64_t, ShmemAllocator>;

class VirtualTime {
public:
  explicit VirtualTime(char const *const name = nullptr, size_t size = 4096 * 64)
      : segment_name_(name ? name : "virtual_time_virtual_time"),
        segment_(boost::interprocess::open_or_create, segment_name_.c_str(), size),
        alloc_inst_(segment_.get_segment_manager()),

        deque_name_(segment_name_ + "-deque"),
        time_buffer_(segment_.find_or_construct<ipc_deque>(deque_name_.c_str())(alloc_inst_)),

        mutex_name_(segment_name_ + "-mutex"), mutex_(boost::interprocess::open_or_create, mutex_name_.c_str()),

        ref_count_name_(segment_name_ + "-ref_count"),
        ref_count_(segment_.find_or_construct<std::atomic<int64_t>>(ref_count_name_.c_str())(0)) {
    ref_count_->fetch_add(1);
  }

  VirtualTime(const VirtualTime &) = delete;
  VirtualTime &operator=(const VirtualTime &) = delete;

  ~VirtualTime() {
    ref_count_->fetch_sub(1);

    std::cout << "ref_count: " << ref_count_->load() << std::endl;

    if (ref_count_->load() <= 0) {
      segment_.destroy<std::atomic<int64_t>>(ref_count_name_.c_str());
      boost::interprocess::named_mutex::remove(mutex_name_.c_str());
      segment_.destroy<ipc_deque>(deque_name_.c_str());
      boost::interprocess::shared_memory_object::remove(segment_name_.c_str());
    }
  }

  void reset() {
    try {
      boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lock(mutex_);
      time_buffer_->clear();
    } catch (std::exception &e) {
      throw e;
    }
  }

  void push(int64_t timestamp) {
    if (timestamp < 0) {
      return;
    }

    try {
      boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lock(mutex_);
      time_buffer_->push_back(timestamp);
      if (time_buffer_->size() > max_buffer_size_) {
        time_buffer_->pop_front();
      }
    } catch (std::exception &e) {
      throw e;
    }
  }

  void get(int64_t &timestamp) {
    try {
      boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lock(mutex_);
      if (time_buffer_->empty()) {
        timestamp = -1;
        return;
      }
      timestamp = *std::max_element(time_buffer_->begin(), time_buffer_->end());
    } catch (std::exception &e) {
      throw e;
    }
  }

private:
  const std::string segment_name_;
  boost::interprocess::managed_shared_memory segment_;
  const ShmemAllocator alloc_inst_;

  const std::string deque_name_;
  ipc_deque *time_buffer_;
  const size_t max_buffer_size_{32};

  const std::string mutex_name_;
  boost::interprocess::named_mutex mutex_;

  const std::string ref_count_name_;
  std::atomic<int64_t> *ref_count_;
};

VirtualTime &VirtualTimeInstance(char const *const name = nullptr, size_t size = 4096 * 64);

} // namespace virtual_time