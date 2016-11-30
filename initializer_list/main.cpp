#include <iostream>
#include <type_traits>
#include <vector>


int main()
{
    std::cout << std::boolalpha;

    auto list = { 'm', 'e', 'e' };

    auto is_initializer_list =
            std::is_same<
                std::initializer_list<char>,
                decltype(list)
            >::value;

    std::cout << "is initializer list: " << is_initializer_list << std::endl;

    // Main use-case: Initialize containers
    std::vector<int> v = { 0, 1, 1, 2, 3, 5 };
    std::vector<char> w = list;

    // This does not compile
    // auto value_list = { 1, 2.0, 3u };
}
