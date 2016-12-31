#include "perfect_forwarding.hh"

#include <iostream>
#include <type_traits>
#include <vector>

namespace
{
    // foo takes a forwarding reference (universal reference) as argument
    template <class T>
    void foo(T&& t)
    {
        std::cout << "Reference qualifier in foo: " << QUALIFIER(t) << std::endl;
    }

    // const_foo takes a const rvalue-reference
    // since moving from const variables is not allowed this leads to the same behaviour as
    // 'const&'
    template <class T>
    void const_foo(const T&& t)
    {
        std::cout << "Reference qualifier in const_foo: " << QUALIFIER(t) << std::endl;
    }

    // vector_foo takes a rvalue-reference as argument
    template <class T>
    void vector_foo(std::vector<T>&& t)
    {
        std::cout << "Reference qualifier in vector_foo: " << QUALIFIER(t) << std::endl;
    }
}


int main()
{
    int i = 0;
    foo(i);

    foo(std::move(i));

    vector_foo(std::vector<int>{});
//    std::vector<int> vec;
//    vector_foo(vec);

    int j = 1;
//    const_foo(j);
    const_foo(std::move(j));

    int a = 2;
    const int b = 3;

    auto&& f = a;
    std::cout << "Reference qualifier of f: " << QUALIFIER( std::forward<decltype(f)>(f) ) << std::endl;

    auto&& g = b;
    std::cout << "Reference qualifier of g: " << QUALIFIER( std::forward<decltype(g)>(g) ) << std::endl;

    auto&& h = 0;
    std::cout << "Reference qualifier of h: " << QUALIFIER( std::forward<decltype(h)>(h) ) << std::endl;

    perfect_forwarding();
}
