#pragma once

#include <iostream>
#include <memory>

void print_weak_ptr(const std::weak_ptr<char>& ptr)
{
    if( auto shared = ptr.lock() )
        std::cout << "contains " << *shared << std::endl;
    else
        std::cout << "empty" << std::endl;
}

void section_weak_ptr()
{
    // std::weak_ptr for pointers that can dangle (don't increase reference count)
    // to be used with std::shared_ptr
    std::weak_ptr<char> wptr;
    print_weak_ptr(wptr);

    {
        auto ptr = std::make_shared<char>('m');
        wptr = ptr;
        print_weak_ptr(wptr);
    }
    print_weak_ptr(wptr);
}
