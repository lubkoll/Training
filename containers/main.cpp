#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <vector>

#include <set>
#include <map>

#include <unordered_set>
#include <unordered_map>

#include <stack>
#include <queue>


int main(int, char*[])
{
    // sequence containers
    std::array<int,4> array; // int array[4];
    std::deque<int> double_ended_queue;
    std::vector<int> vector;
    std::list<int> list; // doubly-linked list
    std::forward_list<int> forward_list; // singly-linked list


    // associative containers
    std::map<int,double> map;
    std::set<int> set;
    std::multiset<int> multiset;
    std::multimap<int,double> multimap;


    // unordered associative container
    std::unordered_map<int,double> unordered_map;
    std::unordered_set<int> unordered_set;
    std::unordered_multimap<int,double> unordered_multimap;
    std::unordered_multiset<int> unordered_multiset;


    // container adaptors
    std::stack<int/*, std::deque<int>*/ > stack; // filo
    std::queue<int/*, std::deque<int>*/ > queue; // fifo
    std::priority_queue<int/*, std::vector<int>*/ > priority_queue;
}
