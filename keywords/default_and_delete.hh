#pragma once

namespace cpp98
{
    class Singleton
    {
    public:
        static Singleton& get()
        {
            static Singleton singleton;
            return singleton;
        }

    private:
        Singleton()
        {}
        Singleton(const Singleton&)
        {}
        Singleton& operator=(const Singleton&)
        {}
    };
}


namespace cpp11
{
    class Singleton
    {
    public:
        static Singleton& get()
        {
            static Singleton singleton;
            return singleton;
        }

        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;

        Singleton(Singleton&&) = delete;
        Singleton& operator=(Singleton&&) = delete;

    private:
        Singleton() = default;
    };
}


template <class T>
void foo(T t)
{
    std::cout << "foo" << std::endl;
}

void foo(int) = delete;


void default_and_delete_example()
{
    foo('c');
    // The following line does not compile, since foo(int) was deleted.
    // foo(0);
}
