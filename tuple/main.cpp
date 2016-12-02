#include <iostream>
#include <string>
#include <set>
#include <tuple>
#include "tuple_printer.hh"


template<class... Args>
void print(const std::tuple<Args...>& t)
{
    std::cout << "(";
    TuplePrinter<decltype(t), sizeof...(Args)>::print(t);
    std::cout << ")\n\n";
}


int main()
{
    // Create tuple with its variadic constructor
    std::tuple<int,double,char> tpl{1, 2.5, 'c'};
    std::cout << "tpl" << std::endl;
    print(tpl);


    // Create tuple with generating function
    // that deduces the argument types
    auto other_tpl = std::make_tuple(1, 2.5, 'c');
    std::cout << "other_tpl" << std::endl;
    print(other_tpl);

    int a = 1;
    double b = 2.3;
    char c = 'd';

    // Create tuple of lvalue-references with std::tie
    auto cmp = std::tie(a,b,c) < tpl;
    std::cout << cmp << std::endl;


    std::set<std::string> set_of_str;
    bool inserted;

    // Use std::ignore as generic placeholder for values you are not interested in
    std::tie(std::ignore, inserted) = set_of_str.insert("Test");
    if (inserted)
        std::cout << "Value was inserted successfully\n";


    std::tuple<int, std::string, float> t1(10, "Test", 3.14f);
    int n = 7;

    // Concatenate tuples with std::tuple_cat
    auto t2 = std::tuple_cat(t1, std::make_pair("Foo", "bar"), t1, std::tie(n));
    n = 10;
    print(t2);
}

