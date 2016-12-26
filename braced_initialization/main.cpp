#include <atomic>
#include <iostream>
#include <vector>
#include <type_traits>

using std::cout;
using std::endl;
using std::is_same;

struct Tmp
{
private:
    int x{0};
    std::atomic<int> y{1};
};


int main()
{
    // initializer lists:
    std::vector<int> v = { 1, 2, 3, 4, 5 };

    // complains about narrowing of builtin types
    double x = 0, y = 1, z = 2;
//    int a{ x + y + z };

    // be careful with braced initialization in conjunction with auto:
    auto b{3};
    auto c = {1};

    cout << is_same<decltype(b), int>::value << endl;
    cout << is_same<decltype(c), std::initializer_list<int> >::value << endl;

    return 0;
}
