#include <iostream>
#include <stdexcept>
#include <memory>

#include "unique_ptr.hh"
#include "shared_ptr.hh"
#include "weak_ptr.hh"


bool throws()
{
    throw std::runtime_error("hi");
}


int main()
{
    std::cout << std::boolalpha;

    // C++98: raw owning pointers
    try {
        auto char_ptr = new char('c');
        if( throws() )
            delete char_ptr;
        delete char_ptr;
    }
    catch (...) {}



    // C++98: std::auto_ptr
    std::auto_ptr<char> char_ptr(new char('c'));

    // looks like a copy, but is not
    std::auto_ptr<char> other_ptr = char_ptr;

//    char c = *char_ptr;

    // C++11: raw pointers are non-owning
    //        for owning pointers use smart pointers

    // unique ownership
    section_unique_ptr();

    // shared ownership
    section_shared_ptr();

    // pointers that can dangle
    section_weak_ptr();
}
