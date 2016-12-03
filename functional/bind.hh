#pragma once

#include <functional>
#include <iostream>

namespace bind
{
    struct Operation
    {
        int add(int x, int y) const { return x + y; }
    };

    void example()
    {
        // std::bind to (partially) bind arguments (add_three holds copies of all arguments)
        auto add_three = std::bind( std::plus<int>{},
                                    3,
                                    std::placeholders::_1 );
        std::cout << add_three(2) << '\n';

        // std::bind with member functions
        auto add_four = std::bind( &Operation::add,
                                   Operation{},
                                   4,
                                   std::placeholders::_1 );
        std::cout << add_four(2) << '\n';

        // often lambdas are easier to understand
        auto add_five = [](int value)
                        {
                            return value + 5;
                        };
        std::cout << add_five(2) << "\n\n";


    }
}
