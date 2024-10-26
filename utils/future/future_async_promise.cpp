// exercise using future, async, promise, packaged_task
// g++ future_async_promise.cpp --std=c++17 -lpthread

#include <cmath>
#include <future>
#include <iostream>
#include <thread>

struct X {
  void operator()(int x) { std::cout << x << std::endl; }
};

double square_root(double x) {
  if (x < 0) {
    throw std::out_of_range("x < 0");
  }
  return std::sqrt(x);
}

void square_root_promise(std::promise<double> p, double x) {
  if (x < 0) {
    // more efficient than try-catch block
    p.set_exception(std::make_exception_ptr(std::out_of_range("x < 0")));
  } else {
    p.set_value(std::sqrt(x));
  }
}

int main() {
  auto f1 = std::async(X(), 42);
  // f1.wait();
  f1.get();

  auto task = std::packaged_task<int(int, int)>([](int a, int b) {
    auto s = a + b;
    std::cout << s << std::endl;
    return s;
  });
  task(1, 2);
  auto f2 = task.get_future();
  std::cout << "f2.get() = " << f2.get() << std::endl;

  std::promise<double> p;
  auto f3 = std::async(square_root, 1);
  std::cout << "f3.get() = " << f3.get() << std::endl;

  auto f4 = std::async(square_root, -1);
  try {
    auto result = f4.get();
    std::cout << "f4.get() = " << result << std::endl;
  } catch (const std::out_of_range &e) {
    std::cout << e.what() << std::endl;
  }

  std::promise<double> p2;
  auto f5 = p2.get_future();
  std::thread t(square_root_promise, std::move(p2), -1);
  try {
    auto result = f5.get();
    std::cout << "f5.get() = " << result << std::endl;
  } catch (const std::out_of_range &e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << "f5.valid() = " << f5.valid() << std::endl;

  t.join();

  return 0;
}
