#include <atomic>
#include <iostream>
#include <vector>
#include <type_traits>

struct Tmp
{
private:
    int x{0};
    // std::atomic has no copy constructor
    std::atomic<int> y{1};
};


int main()
{
    // initializer lists:
    std::vector<int> v = { 1, 2, 3, 4, 5 };

    // complains about narrowing of builtin types
    double x = 0, y = 1, z = 2;
//    int a{ x + y + z };

    // be careful with braced initialization in conjunction with auto,
    // this behaves differently with different compilers,
    // better DON'T use it until you are allowed to use C++17
    auto b{3};
    auto c = {1};

    std::cout << std::boolalpha;
    std::cout << std::is_same<decltype(b), int>::value << std::endl;
    std::cout << std::is_same<decltype(c), std::initializer_list<int> >::value << std::endl;

    // see
    // - Scott Meyers, Effective Modern C++, Item 7
    // - James Dennett, New Rules for auto deduction from braced-init-list, N3922
}
