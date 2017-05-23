#include <iostream>
#include <memory>


class Identifier
{
public:
    explicit Identifier(int val) noexcept
        : value_(val)
    {}

    explicit operator int() const noexcept
    {
        return value_;
    }

private:
    int value_;
};




class Real
{
public:
    explicit Real(double val = 0) noexcept
        : value_(val)
    {}

    explicit operator double() const noexcept
    {
        return value_;
    }

private:
    double value_;
};

inline
bool operator==(Real a, Real b) noexcept
{
    return static_cast<double>(a) == static_cast<double>(b);
}


int main()
{
    std::cout << std::boolalpha;

    Identifier a(1);
    Real b(1);

    // possible wih implicit conversion operator
//    std::cout << (a == b) << std::endl;
    // with explicit conversion operator
    std::cout << ( static_cast<int>(a) == static_cast<double>(b) ) << std::endl;

    // Special case:
    // operator bool
    std::unique_ptr<int> data;
    std::shared_ptr<int> data2;

    // operator bool can be used without explicitly casting if it can be 'contextually converted' to 'bool',
    // i.e. if 'bool t(op);' is well formed, where 'op' denotes the 'operator bool'.
    // Thus, static_cast<bool> is not needed for:
    // - if, while, and for statements
    // - logical negation !, logical conjunction &&, and logical disjunction ||
    // - conditional operator ?:
    // -  static_assert
    // -  noexcept
    // i.e., the following line still works
    if(data && data2) {
        // do something
    }

    // No need for the 'safe bool idiom' (http://www.artima.com/cppsource/safebool.html)
}
