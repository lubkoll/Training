#include <algorithm>
#include <iostream>
#include <utility>


std::vector<int> create_vector()
{
    return { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
}

namespace project1
{
    struct Vector
    {
        template <class... Args,
                  std::enable_if_t<
                      std::is_constructible< std::vector<int>, Args... >::value &&
                      !std::is_constructible< Vector, Args... >::value
                   >* = nullptr>
        explicit Vector(Args&&... args)
            : data(std::forward<Args>(args)...)
        {}

        std::vector<int> data;
    };

    auto begin(Vector& v) -> decltype(begin(v.data))
    {
        return begin(v.data);
    }

    auto end(Vector& v) -> decltype(end(v.data))
    {
        return end(v.data);
    }

    Vector create_vector()
    {
        return Vector(::create_vector());
    }
}

namespace project2
{
    struct Vector
    {
        template <class... Args,
                  std::enable_if_t<
                      std::is_constructible< std::vector<int>, Args... >::value &&
                      !std::is_constructible< Vector, Args... >::value
                  >* = nullptr>
        explicit Vector(Args&&... args)
            : data(std::forward<Args>(args)...)
        {}

        auto begin()
        {
            return data.begin();
        }

        auto end()
        {
            return data.end();
        }

        std::vector<int> data;
    };

    Vector create_vector()
    {
        return Vector(::create_vector());
    }
}


int main()
{
    auto printer = [](auto&& i) { std::cout << std::forward<decltype(i)>(i) << ' '; };
    // Use std::begin and std::end instead of the corresponding member functions.
    {
    // If you want to have the stl-implementations (which just call the member functions) uncomment the following two lines
//     using std::begin;
//     using std::end;
}

    auto v = create_vector();

    std::for_each( begin(v), end(v), printer);
    std::cout << '\n';

    std::sort( begin(v), end(v) );

    std::for_each( begin(v), end(v), printer);
    std::cout << '\n';

    // cbegin() and cend() can be treated analogously.
}
