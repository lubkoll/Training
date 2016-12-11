#pragma once

#include <algorithm>
#include <functional>
#include <iostream>
#include <tuple>
#include <vector>

auto get_add_to_offset_bad()
{
    int offset = 3;
    // Captures local variable by reference
    // -> reference will dangle
    return [&offset] (int i) { return offset + i; };
}

auto get_add_to_offset_worse()
{
    int offset = 3;
    // Captures all variables by reference
    // -> in general we don't even know which references might dangle
    return [&] (int i) { return offset + i; };
}

auto get_add_to_offset_good()
{
    int offset = 3;
    // Captures local variable by value
    return [offset] (int i) { return offset + i; };
}

auto get_add_to_offset_bad2()
{
    int offset = 3;
    // Captures local variable by value
    // Safe here, but may be unsafe in other use-cases
    return [=] (int i) { return offset + i; };
}

auto get_add_to_offset_bad3()
{
    static int offset = 3;
    auto lambda = [=](int i) { return offset + i; };
    offset++;
    return lambda;
}


class AddToOffset
{
public:
    auto get() const
    {
        // Here offset can not be captured, since it is a member variable.
        // Instead 'this' gets captured by value
        // -> this may dangle
        return [=] (int i) { return offset + i; };
    }

private:
    int offset = 3;
};

struct IsOdd
{
    int operator()(int i)
    {
        return i%2;
    }
};


namespace cpp11
{
    void lambda()
    {
        std::vector<int> v = { 1, 2, 3, 4, 5 };

        std::cout << "C++98/03:" << std::endl;
        auto odd_elements = std::count_if( begin(v), end(v),
                                           IsOdd() );
        std::cout << "odd_elements: " << odd_elements << "\n\n";

        std::cout << "C++11:" << std::endl;
        odd_elements = count_if( begin(v), end(v),
                                 []( int i ) { return i%2; }
                               );
        std::cout << "odd_elements: " << odd_elements << "\n\n";


        // Structure of lambda expressions:
        // [ capture-list ] ( parameters ) -> return-type { body }
        // [ capture-list ] ( parameters ) mutable -> return-type { body }
        // The return type can be implicitly deduced if the body consists of a single return statement.
        auto get_one = []{ return 1; };
        std::cout << "get_one(): " << get_one() << std::endl;

        auto add_one = [](int i) -> int
        {
            auto result = i + 1;
            return result;
        };
        std::cout << "add_one(1): " << add_one(1) << "\n\n";

        // Using the capture list (only non-static local variables can be captured):
        // Capture by reference (dangerous, reference may dangle
        auto add_to_offset = get_add_to_offset_bad();
        std::cout << "add_to_offset(1): " << add_to_offset(1) << std::endl;

        auto add_to_offset2 = AddToOffset().get();
        std::cout << "add_to_offset2(1): " << add_to_offset2(1) << std::endl;

        auto add_to_offset3 = get_add_to_offset_bad3();
        std::cout << "add_to_offset3(1): " << add_to_offset3(1) << std::endl;

        // The lambda expressions lets the compiler generate a class with
        // const function call-operator. Thus captured variables are immutable.
        // To generate non-const function call operator use 'mutable':
        auto offset = 1;
        auto increase_offset = [offset] () mutable
        {
          offset = offset + 2;
          return offset;
        };
        std::cout << "increase_offset: " << increase_offset() << std::endl;
    }
}
