#pragma once

#include <array>
#include <iostream>

/*
 * C++11: 'constexpr' implies 'const'
 * C++14: 'constexpr' does not imply 'const'
 */
const constexpr int dim = 3;

// constexpr functions can be applied to compile-time and runtime-arguments
constexpr int add(int a, int b)
{
    return a + b;
}

// Point can be constructed at compile-time.
// Its members can also be accessed at compile-time.
class Point
{
public:
    explicit constexpr Point(double x=0, double y=0)
        : x_(x), y_(y)
    {}

    constexpr double x() const
    {
        return x_;
    }

    constexpr double y() const
    {
        return y_;
    }

private:
    double x_, y_;
};

void constexpr_example()
{
    // constexpr
    int a = 1;
    int b = 2;
    std::cout << "1 + 2 = " << add(a,b) << std::endl;

    std::array<char, add(1,2)> arr;
    std::cout << "array.size() = " << arr.size() << std::endl;

    std::array<char, int( Point(3,5).y() )> arr2;
    std::cout << "arr2.size() = " << arr2.size() << "\n\n";
}
