#pragma once

#include <functional>

namespace mem_fn
{
    struct T
    {
        explicit T(int val) : value(val) { }

        int get() const
        {
            return value;
        }

        int value = 0;
    };

    void example()
    {
        T s{1}, t{2};

        auto getter = std::mem_fn(&T::get);

        std::cout << getter(s) << '\n';
        std::cout << getter(t) << "\n\n";
    }
}
