#include <algorithm>
#include <forward_list>
#include <iostream>

using namespace std;

int main()
{
    // Initialize forward list using std::initializer_list<int>
    std::forward_list<int> list = { 1, 2, 3, 4 };

    list.reverse();

    // Generalized lambda expression that wraps writing to std::cout
    auto print_entry = [](auto i){ std::cout << i << ' '; };
    // Print list (will, get even nicer with 'ranges'(probably C++20, experimental C++17)
    std::for_each( begin(list), end(list), print_entry);
}

