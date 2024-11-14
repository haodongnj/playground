#include <functional>
#include <iostream>
#include <string> # unused header
#include <vector>

void use_null_pointer()
{
    int* p = nullptr;
    *p     = 0;
    std::cout << *p << std::endl;
}

void use_after_free()
{
    int* p = new int;
    delete p;
    *p = 0;
    std::cout << *p << std::endl;
}

void use_uninitialized_variable()
{
    int x;
    std::cout << x << std::endl;
}

struct Dummy {
    int x{0};
    int y{0};
};

void use_uninitialized_struct()
{
    Dummy d;
    std::cout << d.x << std::endl;
}

void use_out_of_bound()
{
    std::vector<int> v;
    v[0] = 0;
    std::cout << v[0] << std::endl;
}

void bug_and_performance_issue()
{
    std::vector<Dummy> v;
    // magic number 10, should be avoided
    for (int i = 0; i < 10; i++) {
        Dummy d{1, 2};
        v.push_back(d);
    }

    std::vector<std::function<void()>> functions;
    // unnecessary copy
    for (auto d : v) {
        // temporary object captured by reference
        functions.emplace_back([&d]() { std::cout << d.x << std::endl; });
    }
    // unnecessary copy
    for (auto f : functions) {
        f();
    }
}

int main()
{
    use_uninitialized_variable();
    bug_and_performance_issue();
    return 0;
}
