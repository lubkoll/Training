#pragma once

#include <utility>
#include <type_traits>

namespace cpp98
{
    void f() throw() {}
}

namespace cpp11
{
    // does not require unwindable stack
    // -> better optimizable by the compiler
    void f() noexcept {};



    template <class T>
    struct Container
    {
        template <class... Args,
                  std::enable_if_t< std::is_constructible<T,Args...>::value >* = nullptr>
        explicit Container(Args&&... args) noexcept(std::is_constructible<T,Args...>::value)
        {
            return T(std::forward<Args>(args)...);
        }
    };
}

void noexcept_example()
{
}
