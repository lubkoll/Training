#pragma once


namespace auto_type_deduction
{
    template <class T>
    void f(T t)
    {}


    template <class T>
    void g(const T& t)
    {}


    template <class T>
    void h(T& t)
    {}


    void example()
    {
        int             i = 1;
        const int      ci = i;
        int&        i_ref = i;
        const int& ci_ref = i;

        // Type deduced for 'auto':
        // Type of 'x0'           :
        auto x0 = i;

        // Type deduced for 'auto':
        // Type of 't1'           :
        auto x1 = ci;

        // Type deduced for 'auto':
        // Type of 'x2'           :
        auto x2 = ci_ref;

        // Type deduced for 'auto':
        // Type of 'y0'           :
        auto& y0 = i;

        // Type deduced for 'auto':
        // Type of 'y1'           :
        auto& y1 = ci;

        // Type deduced for 'auto':
        // Type of 'y2'           :
        auto& y2 = i_ref;

        // Type deduced for 'auto':
        // Type of 'y3'           :
        auto& y3 = ci_ref;
    }
}


