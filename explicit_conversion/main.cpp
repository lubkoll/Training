#include <iostream>
#include <memory>


class Identifier
{
public:
    Identifier(int val) noexcept
        : value_(val)
    {}

    operator int() const noexcept
    {
        return value_;
    }

private:
    int value_;
};


bool operator==(Identifier a, Identifier b) noexcept
{
    return static_cast<int>(a) == static_cast<int>(b);
}


class Real
{
public:
    Real(double val = 0) noexcept
        : value_(val)
    {}

    operator double() const noexcept
    {
        return value_;
    }

private:
    double value_;
};


bool operator==(Real a, Real b) noexcept
{
    return static_cast<double>(a) == static_cast<double>(b);
}


int main()
{
    std::cout << std::boolalpha;

    Identifier a(1);
    Real b(1);

    std::cout << (a == 2) << std::endl;
//    cout << ( static_cast<int>(a) == static_cast<double>(b) ) << endl;

    // Special case:
    // operator bool
    std::unique_ptr<int> data;
    if(data) {
        // do something
    }

    // No need for the 'safe bool idiom'
    // see http://www.artima.com/cppsource/safebool.html
}
