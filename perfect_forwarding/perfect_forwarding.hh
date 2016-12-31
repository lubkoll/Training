#pragma once

#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>

#define QUALIFIER(variable) \
    ( std::is_same< decltype(variable), typename std::decay<decltype(variable)>::type >::value ? std::string("\n") :  \
      std::is_same< decltype(variable), const typename std::decay<decltype(variable)>::type >::value ? std::string("const\n") :  \
      std::is_same< decltype(variable), typename std::decay<decltype(variable)>::type& >::value ? std::string("&\n") : \
      std::is_same< decltype(variable), const typename std::decay<decltype(variable)>::type& >::value ? std::string("const&\n") : \
      std::is_same< decltype(variable), typename std::decay<decltype(variable)>::type&& >::value ? std::string("&&\n") : \
      std::string("const&&\n") )




void boo(int&)
{
    std::cout << "Reference qualifier in boo: &\n";
}

void boo(const int&)
{
    std::cout << "Reference qualifier in boo: const&\n";
}

void boo(int&&)
{
    std::cout << "Reference qualifier in boo: &&\n";
}

template <class T>
void bar(T&& t)
{
    std::cout << "Reference qualifier in bar: " << QUALIFIER(t);
}

template <class T>
void foobar(T&&)
{
    std::cout << "foobar(T&&)" << std::endl;
}

void foobar(const int&)
{
    std::cout << "foobar(const int&)" << std::endl;
}

//void foobar(int)
//{
//    std::cout << "foobar(int)" << std::endl;
//}

class Data
{
    using Buffer = std::vector<int>;
public:
    template <typename... Args,
              class = std::enable_if_t<
                  std::is_constructible<Buffer,Args...>::value &&
                  !std::is_constructible<Data,Args...>::value
                  >
              >
    explicit Data(Args&&... args)
        : buffer_( std::forward<Args>(args)... )
    {
        std::cout << "buffer size: " << buffer_.size() << std::endl;
    }

    static const int declared_only = 42;
    static const int defined;

private:
    Buffer buffer_;
};

const int Data::defined = 73;


void perfect_forwarding()
{
    int i = 0;
    const int ci = 0;

    // classical overloading:
    boo(i);
    boo(ci);
    boo(0);

    // forwarding references
    bar(i);
    bar(ci);
    bar(0);

    // be careful when combining overloading with forwarding references
    foobar(i);
    foobar(ci);
    foobar(0);

    // forwarding constructors
    const Data data(4, 2);
    Data other_data(data);


    // Failure cases

    // - braced initializers

    // This does not compile:
    // Data more_data( {1} );

    auto initializer = { 1 };
    Data more_data(initializer);

    // - Static member variables:
    Data from_defined( Data::defined );

//    Data from_declared( Data::declared_only );
}
