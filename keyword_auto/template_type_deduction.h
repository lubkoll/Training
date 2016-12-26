#pragma once


namespace template_type_deduction
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

        // Type deduced for 'T':
        // Type of 't'         :
        f(i);

        // Type deduced for 'T':
        // Type of 't'         :
        f(ci);

        // Type deduced for 'T':
        // Type of 't'         :
        f(i_ref);

        // Type deduced for 'T':
        // Type of 't'         :
        f(ci_ref);

        // Type deduced for 'T':
        // Type of 't'         :
        g(i);

        // Type deduced for 'T':
        // Type of 't'         :
        g(ci);

        // Type deduced for 'T':
        // Type of 't'         :
        g(i_ref);

        // Type deduced for 'T':
        // Type of 't'         :
        g(ci_ref);

        // Type deduced for 'T':
        // Type of 't'         :
        h(i);

        // Type deduced for 'T':
        // Type of 't'         :
        h(ci);

        // Type deduced for 'T':
        // Type of 't'         :
        h(i_ref);

        // Type deduced for 'T':
        // Type of 't'         :
        h(ci_ref);
    }
}


