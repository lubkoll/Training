#include <iostream>
#include <string>
#include <tuple>

// Iterate over sequence of types
template <class...>
struct ForEach;

// Iteration
template <class Arg, class... Args>
struct ForEach<Arg, Args...>
{
    template <template <class> class Operation>
    static void apply()
    {
        Operation<Arg>::apply();
        ForEach<Args...>::template apply<Operation>();
    }
};

// Terminate iteration
template <>
struct ForEach<>
{
    template <template <class> class Operation>
    static void apply() {}
};


// Print the size of Arg.
template <class Arg>
struct PrintSize
{
    static void apply()
    {
        std::cout << "size: " << sizeof(Arg) << std::endl;
    }
};


// Wrapper function for more elegant usage.
template <class... Args>
void print_size()
{
    ForEach<Args...>::template apply<PrintSize>();
}




template<typename Function,
         typename Tuple,
         std::size_t... indices>
decltype(auto) invoke_helper(Function&& f, Tuple&& args, std::index_sequence<indices...>)
{
    // unpack args using
    return f(std::get<indices>(std::forward<Tuple>(args))...);
}

// Invoke function with arguments stored i.e. in a std::tuple
template<typename Function,
         typename Tuple>
decltype(auto) invoke(Function&& f, Tuple&& args)
{
    constexpr auto tuple_size = std::tuple_size<typename std::decay<Tuple>::type>::value;
    return invoke_helper(std::forward<Function>(f),
                         std::forward<Tuple>(args),
                         // 0 1 ... (tuple__size-1)
                         std::make_index_sequence<tuple_size>{});
}


void print_sizes(int i, char c, double d)
{
    std::cout << "sizeof(i): " << sizeof(i) << std::endl;
    std::cout << "sizeof(c): " << sizeof(c) << std::endl;
    std::cout << "sizeof(d): " << sizeof(d) << std::endl;
}

int main()
{
    print_size<int, char, short, long, std::string>();

    auto args = std::make_tuple(1,'c',2.0);
    invoke(print_sizes, args);
}
