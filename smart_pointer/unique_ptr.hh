#pragma once

#include <chrono>
#include <memory>

struct ThrowsInConstructor
{
    ThrowsInConstructor()
    {
        if( std::rand() > 0)
            throw std::runtime_error("hello");
    }
};

void process_2_ptrs(std::unique_ptr<ThrowsInConstructor> lhs, std::unique_ptr<ThrowsInConstructor> rhs)
{}

void section_unique_ptr()
{
    {
        std::unique_ptr<char> ptr(new char('c'));

        // does not compile:
    //    std::unique_ptr<char> other_ptr = ptr;

        // need to move
        std::unique_ptr<char> other_ptr = std::move(ptr);

        // even better with C++14 (forgotten in C+11):
        auto ptr2 =  std::make_unique<char>('c');
    }

    {
        // Why use std::make_unique instead of the constructor?

        // 1. Because this may leak memory:
        try {
            process_2_ptrs( std::unique_ptr<ThrowsInConstructor>( new ThrowsInConstructor() ),
                            std::unique_ptr<ThrowsInConstructor>( new ThrowsInConstructor() ) );
        } catch(...) {}

        // 2. Because of the symmetry of new/delete, resp. malloc/free

        // 3. Less code duplication:
        // type mentioned twice:
        auto ptr1 = std::unique_ptr<char>(new char('c'));
        // type mentioned once:
        auto ptr2 = std::make_unique<char>('c');

        // 4. Teaching others
    }

    {
        // Don't use std::make_unique if
        // 1. you get the raw pointer from elsewhere (i.e. a factory)
        // 2. you need a custom deleter:
        auto deleter = [](char* ptr) { delete ptr; };
        // Custom deleter is part of the type!
        auto ptr = std::unique_ptr<char, decltype(deleter)>( new char('c'), deleter );
    }
}
