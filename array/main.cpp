#include <algorithm>
#include <array>
#include <iostream>
#include <type_traits>

// In C++11, constexpr implies const,
// in C++14 this is not the case any more.
const constexpr int dim = 3;

int main()
{
    std::cout << std::boolalpha;

    // Initialize array using std::initializer_list<int>
    std::array<int, dim> v = { 1, 2, 3 };

    // Replace entries x with x^2 using a generalized lambda expression
    std::transform(begin(v), end(v),
                   begin(v),
                   [](auto x) { return x *= x; } );

    // Print with range-based for-loop
    for(auto entry : v)
        std::cout << entry << " ";
    std::cout << "\n";

    // Access underlying type:
    std::cout << "is int: " << std::is_same< int, decltype(v)::value_type >::value << std::endl;
    std::cout << "is first entry of type int: " << std::is_same< int, std::tuple_element<0, decltype(v)>::type >::value << std::endl;

    // Public member functions:
    // Access via square-bracket-operator
    std::cout << "v[2] = " << v[2] << std::endl;

    // Access via 'at(size_type i)', may throw std::out_of_range
    int v3 = 0;
    try {
        int tmp = v.at(3);
        v3 = tmp;
    } catch (const std::out_of_range& exception) {
        std::cout << "v.at(3) throws" << std::endl;
    }
    std::cout << "v3 = " << v3 << std::endl;

    std::cout << "first and last element: " << v.front() << ", " << v.back() << std::endl;

    // Direct access to underlying data
    std::for_each(v.data(), v.data()+3,
                  [](int i) { std::cout << i << " "; });

    // const reverse iterator -> see also begin()/end(), cbegin()/cend() and rbegin()/rend()
    std::for_each(v.crbegin(), v.crend(),
                  [](int i) { std::cout << i << " "; });
    std::cout << "\n";

    std::cout << "empty: " << v.empty() << std::endl;
    std::cout << "size: " << v.size() << " or " << std::tuple_size<decltype(v)>::value << std::endl;
    std::cout << "max_size: " << v.max_size() << std::endl;

    // Non-member functions
    auto w = v;
    w.fill(1);
    swap(v,w);

    std::cout << "v < w: " << (v < w) << std::endl;
    // and all the other comparison operators (using lexicographical comparison)...
}

