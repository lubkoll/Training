#pragma once

#include <iostream>

void guarantees_initialization()
{
    // auto-declared variables require initialization,
    // which helps to avoid subtle errors due to uninitialized variables.
    int x;

    // looks good on gcc, but try with clang
    std::cout << "x = " << x << std::endl;

    // This does not compile:
    // auto y;

    // Only initialized variables are admissible
    auto z = 0;
}
