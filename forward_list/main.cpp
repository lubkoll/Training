#include <algorithm>
#include <forward_list>
#include <iostream>

using namespace std;

int main()
{
    std::forward_list<int> list = { 1, 2, 3, 4 };

    list.reverse();

    auto print_entry = [](int i){ std::cout << i << ' '; };

    std::for_each( begin(list), end(list), print_entry);

    std::cout << std::endl;
    return 0;
}

