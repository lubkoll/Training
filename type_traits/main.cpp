#include <iostream>
#include <type_traits>

// Macro to print some properties of T
#define PRINT(T) \
    std::cout << #T << std::endl; \
    std::cout << "no-throw default-constructible : " << std::is_nothrow_default_constructible<T>::value << std::endl; \
    std::cout << "copy-constructible             : " << std::is_copy_constructible<T>::value << std::endl; \
    std::cout << "copy-assignable                : " << std::is_copy_assignable<T>::value << std::endl; \
    std::cout << "move-constructible             : " << std::is_move_constructible<T>::value << std::endl; \
    std::cout << "move-assignable                : " << std::is_move_assignable<T>::value << std::endl; \
    std::cout << std::endl


struct NonCopyable
{
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;

    NonCopyable(NonCopyable&&) = default;
    NonCopyable& operator=(NonCopyable&&) = default;
};

struct NonMoveable
{
    NonMoveable() = default;
    NonMoveable(const NonMoveable&) = default;
    NonMoveable& operator=(const NonMoveable&) = default;

    NonMoveable(NonMoveable&&) = delete;
    NonMoveable& operator=(NonMoveable&&) = delete;

};

struct Default{};


int main()
{
    // Print boolean values as 'true'/'false' instead of 1/0
    std::cout << std::boolalpha;

    PRINT(NonCopyable);
    PRINT(NonMoveable);
    PRINT(Default);


    auto a = 0;
    auto&& b = a;
    auto&& c = 1;

    using namespace std;
    cout << "reference type of b (&|&&): " << is_lvalue_reference<decltype(b)>::value << " | " << is_rvalue_reference<decltype(b)>::value << endl;
    cout << "reference type of c (&|&&): " << is_lvalue_reference<decltype(c)>::value << " | " << is_rvalue_reference<decltype(c)>::value << endl;
    cout << endl;

    cout << "a is of same type as b                   : " << is_same< decltype(a), decltype(b) >::value << endl;
    cout << "a is of same type as b without references: " << is_same< decltype(a), remove_reference_t<decltype(b)> >::value << endl;

    // and much more..., see
    // http://en.cppreference.com/w/cpp/header/type_traits
}
