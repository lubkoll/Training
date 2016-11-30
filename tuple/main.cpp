#include <iostream>
#include <string>
#include <tuple>


template<class Tuple, std::size_t N>
struct TuplePrinter {
    static void print(const Tuple& t)
    {
        TuplePrinter<Tuple, N-1>::print(t);
        std::cout << ", " << std::get<N-1>(t);
    }
};

template<class Tuple>
struct TuplePrinter<Tuple, 1> {
    static void print(const Tuple& t)
    {
        std::cout << std::get<0>(t);
    }
};


template<class... Args>
void print(const std::tuple<Args...>& t)
{
    std::cout << "(";
    TuplePrinter<decltype(t), sizeof...(Args)>::print(t);
    std::cout << ")\n\n";
}


int main()
{
    std::tuple<int,double,char> tpl{1, 2.5, 'c'};
    std::cout << "tpl" << std::endl;
    print(tpl);


    auto other_tpl = std::make_tuple(1, 2.5, 'c');
    std::cout << "other_tpl" << std::endl;
    print(other_tpl);

    int a = 1;
    double b = 2.3;
    char c = 'd';

    auto cmp = std::tie(a,b,c) < tpl;
    std::cout << cmp << std::endl;


    std::tuple<int, std::string, float> t1(10, "Test", 3.14);
    int n = 7;
    auto t2 = std::tuple_cat(t1, std::make_pair("Foo", "bar"), t1, std::tie(n));
    n = 10;
    print(t2);
}

