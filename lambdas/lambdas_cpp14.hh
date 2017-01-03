#pragma once

#include <algorithm>
#include <functional>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

namespace cpp14
{
    void lambda()
    {
        std::vector<int> v = { 1, 2, 3, 4, 5 };

        std::cout << "C++11:" << std::endl;
        auto odd_elements = count_if( begin(v), end(v),
                                      []( int i ) { return i%2; }
                                    );
        std::cout << "odd_elements: " << odd_elements << "\n\n";

        std::cout << "C++14 (generalized lambda expressions):" << std::endl;
        odd_elements = count_if( begin(v), end(v),
                                 []( auto i ) { return i%2; }
                               );
        std::cout << "odd_elements: " << odd_elements << "\n\n";

        std::cout << "C++14 (generalized lambda expressions):" << std::endl;
        odd_elements = count_if( begin(v), end(v),
                                 []( auto&& i ) { return std::forward<decltype(i)>(i) % 2; }
                               );
        std::cout << "odd_elements: " << odd_elements << "\n\n";



        // Structure of lambda expressions:
        // [ capture-list ] ( parameters ) -> return-type { body }
        // [ capture-list ] ( parameters ) mutable -> return-type { body }
        // The return type will be deduced in the same way as for functions with auto return type
        auto get_one = []{ return 1; };
        std::cout << "get_one(): " << get_one() << std::endl;

        auto add_one = [](int i)
        {
            auto result = i + 1;
            return result;
        };
        std::cout << "add_one(1): " << add_one(1) << "\n\n";


        // Generalized lambda capture:
        auto offset1 = 1;
        auto add_to_offset1 = [offset = offset1](int i)
        {
            return offset + i;
        };
        std::cout << "add_to_offset1(1): " << add_to_offset1(1) << std::endl;

        auto offset2 = 1;
        auto add_to_offset2 = [&offset2](int i)
        {
            return offset2 + i;
        };
        offset2 = 2;
        std::cout << "add_to_offset2(1): " << add_to_offset2(1) << std::endl;

        auto offset3 = 3;
        auto add_to_offset3 = [offset = std::move(offset3)](int i)
        {
            return offset + i;
        };
        std::cout << "add_to_offset3(1): " << add_to_offset3(1) << std::endl;
    }
}
