#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <string>

namespace cpp98
{
    // standard typedef
    typedef std::map<int,int> IntMap;

    // typedef for function pointer type
    typedef void (*FunctionType)(int, const std::string&);

    // typedef can't be templated, workaround:
    template <class T>
    struct MakeStringMap
    {
        typedef std::map<T,std::string> type;
    };

    // Get pi for different types.
    template <class T>
    struct pi
    {
        static const T value = 3.1415926535897932385;
    };
}

namespace cpp11
{
    // alias
    using IntMap = std::map<int,int>;

    // alias for function pointer type
    using FunctionType = void(*)(int, const std::string&);

    // template alias
    template <class T>
    using StringMap = std::map<T,std::string>;

    // Get pi for different types.
    template <class T>
    struct pi
    {
        static const T value = 3.1415926535897932385;
    };
}

namespace cpp14
{
    // alias
    using IntMap = std::map<int,int>;

    // alias for function pointer type
    using FunctionType = void(*)(int, const std::string&);

    // template alias
    template <class T>
    using StringMap = std::map<T,std::string>;

    // Get pi for different types.
    template<typename T>
    constexpr T pi = T(3.1415926535897932385);
}


int main()
{
    std::cout << std::setprecision(std::numeric_limits<double>::digits10 + 1);
    std::cout << cpp14::pi<double> << std::endl;
    std::cout << cpp14::pi<float> << std::endl;
    std::cout << cpp14::pi<int> << std::endl;
}
