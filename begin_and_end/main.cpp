#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

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



// Requirement 1: move- and/or copyable (for storage in containers)
// Requirement 2: either member functions begin() and end() or implementations of the free functions
//                begin(...) and end(...) (in its namespace)
// Requirement 3: provides operator<< (in its namespace)
int main()
{
    using namespace std;

    auto printer = [](const auto& i) { std::cout << i << ' '; };

    // Use std::begin and std::end instead of the corresponding member functions.
    // If you want to have the stl-implementations as fallback uncomment the following two lines
    using std::begin;
    using std::end;
    auto v = create_vector();
//    int v[10] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
//    auto v = project1::create_vector();
//    auto v = project2::create_vector();

    // independent
    std::for_each( begin(v), end(v), printer );
    std::cout << '\n';

    std::sort( begin(v), end(v) );

    std::for_each( begin(v), end(v), printer );
    std::cout << '\n';
}
