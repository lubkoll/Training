#pragma once

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

namespace mem_fn
{
    struct Service
    {
        void print() const
        {
            std::cout << this << std::endl;
        }
    };

    template<class Container>
    void print_container(const Container& container)
    {
        for_each(begin(container),
                 end(container),
                 std::mem_fn(&Service::print));
    }

    void example()
    {
        std::vector<Service> services(10);
        print_container(services);
    }
}

