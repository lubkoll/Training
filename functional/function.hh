#pragma once

#include <functional>
#include <iostream>

namespace function
{
    void reference_wrapper_example();

    void invoke(const std::function<const char*()>& f)
    {
        std::cout << ( f ? f() : "empty function"  ) << "\n";
    }

    const char* get_five()
    {
        return "5";
    }

    void example()
    {
        std::function<const char*()> f;

        invoke(f);

        f = []{ return "3"; };
        invoke(f);

        f = nullptr;
        invoke(f);

        f = get_five;
        invoke(f);
        std::cout << "\n";

//        reference_wrapper_example();
    }


    struct T
    {
        void operator()(int new_value)
        {
            value = new_value;
        }

        int value = 0;
    };

    void reference_wrapper_example()
    {
        T t;
        std::function<void(int)> g = t;
        g(3);
        std::cout << "t.value = " << t.value << "\n";

        // Use std::ref/std::cref to store references in std::function:
        g = std::ref(t);
        g(3);
        std::cout << "t.value = " << t.value << "\n";
    }
}
