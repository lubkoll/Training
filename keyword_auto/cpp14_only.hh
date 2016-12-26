#pragma once

#include <iostream>
#include "util.hh"

void cpp14_only()
{
    using std::cout;
    using std::endl;

    // C++14: decltype(auto)
    // use auto with decltype-type-deduction

    decltype(auto) a = 1;
    cout << "decltype(a) = int " << QUALIFIER(a) << endl;

    decltype(auto) b = a;
    cout << "decltype(b) = int " << QUALIFIER(b) << endl;

    auto& c = a;
    decltype(auto) d = c;
    cout << "decltype(d) = int " << QUALIFIER(d) << endl;
}
