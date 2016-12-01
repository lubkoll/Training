#include <algorithm>
#include <array>
#include <iostream>

// In C++11, constexpr implies const,
// in C++14 this is not the case any more.
const constexpr int dim = 3;

int main()
{
    // Initialize array using std::initializer_list<int>
    std::array<int, dim> v = { 1, 2, 3 };

    // Replace entries x with x^2 with a generalized lambda expression
    std::for_each( begin(v), end(v),
                   [] (auto& x) { x *= x; } );

    // Print with range-based for-loop
    for(auto entry : v)
        std::cout << entry << " ";
}

