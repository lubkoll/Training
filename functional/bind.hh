#pragma once

#include <functional>
#include <iostream>

namespace bind
{
    struct Operation
    {
        int add(int x, int y) const { return x + y; }
    };

    struct NonCopyable
    {
        NonCopyable(const NonCopyable&) = delete;
        NonCopyable& operator=(const NonCopyable&) = delete;

        NonCopyable(NonCopyable&&) = default;
        NonCopyable& operator=(NonCopyable&&) = default;
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


        // In C++11, we can use std::bind to emulate generalized lambda capture.
        // This admits to capture non-copyable, moveable types in C++11:

        // C++14:
        NonCopyable non_copyable1;
        auto use_non_copyable_14 = [non_copyable = std::move(non_copyable1)] { /*do something*/ };

        // C++11 emulation:
        NonCopyable non_copyable2;
        auto use_non_copyable_11 = std::bind( [](const NonCopyable& non_copyable) { /* do something */ },
                                              std::move(non_copyable2) );

        // resp.
        NonCopyable non_copyable3;
        auto modify_non_copyable_11 = std::bind( [](NonCopyable& non_copyable) mutable { /* do something */ },
                                                 std::move(non_copyable3) );
    }
}
