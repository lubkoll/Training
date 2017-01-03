#pragma once

#include <fung/fung.hh>

#include <iostream>

static const constexpr int id = 0;

inline auto generate_function()
{
    using namespace FunG;
    auto x = variable<id>(1.0);
    return x*x - 2*x + 1;
}

inline void work_with_unknown_and_difficult_types()
{
    auto f = generate_function();
    f.update<id>(3.0);
    std::cout << "f(3) = " << f() << std::endl;

//    using open_sesame = decltype(f)::open_sesame;

    auto g = [](int i) { return i*i; };
}
