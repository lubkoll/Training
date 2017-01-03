#pragma once

namespace auto_return_values
{
    // This does not compile:
    // auto create_initializer_list() {
    //     return { 1 };
    // }


    // C++11
    auto f()
    {
        return 1 + 1;
    }

    auto g(int i) -> int
    {
        if(i%2)
            return 1;

        return 2;
    }


    // C++14
    auto h(int i)
    {
        if(i%2)
            return 1;

        return 2;
    }


    void example()
    {
        auto x = f();
        auto y = g(1);
        auto z = h(2);
    }
}
