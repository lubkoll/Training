#include <algorithm>
#include <array>
#include <iostream>

const constexpr int dim = 3;

int main()
{
    std::array<int, dim> v = { 1, 2, 3 };

    std::for_each( begin(v), end(v),
                   [] (auto& x) { x *= x; } );


    using Index = decltype(v.size());
    for(Index i = 0; i < v.size(); ++i)
        std::cout << v[i] << " ";
    std::cout << std::endl;

    return 0;
}

