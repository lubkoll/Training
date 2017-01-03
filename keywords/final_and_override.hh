#pragma once

#include <iostream>
#include <memory>

struct Base
{
    virtual ~Base() = default;
    virtual void foo() const = 0;
    virtual void bar() const = 0;
};

struct Derived : Base
{
    // Always use 'override' when overriding virtual functions.
    void foo() const override
    {
        std::cout << "Derived::foo" << std::endl;
    }

    // Use 'final' when 'bar' should not be overwritten in classes deriving from 'Derived'
    void bar() const final override
    {
        std::cout << "Derived::bar should not be overwritten" << std::endl;
    }
};

struct Derived2 : Derived
{
    void foo()
    {
        std::cout << "Derived2::foo" << std::endl;
    }

    // Cannot declare 'void bar() const' since it is final in Derived
//    void bar() const
//    {}
};

// Disallow deriving from Derived3.
struct Derived3 final : Base
{
    void foo() const override
    {
        std::cout << "Derived3::foo" << std::endl;
    }

    void bar() const override
    {
        std::cout << "Derived3::bar" << std::endl;
    }
};

// This does not compile:
// struct Derived4 : Derived
// {};

void final_and_override_example()
{
    std::unique_ptr<Base> base = std::make_unique<Derived>();
    base->foo();
    base->bar();

    base = std::make_unique<Derived2>();
    base->foo();
    base->bar();

    base = std::make_unique<Derived3>();
    base->foo();
    base->bar();
}
