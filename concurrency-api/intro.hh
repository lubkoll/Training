#pragma once

#include <algorithm>
#include <chrono>
#include <future>
#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <thread>

using std::cout;
using std::endl;

using Iterator = typename std::vector<std::string>::iterator;
using Size = typename std::iterator_traits<Iterator>::difference_type;

namespace intro
{
    Size count_a(Iterator start_iterator, Iterator end_iterator)
    {
        auto count_a_in_string = [](Size counter, const std::string& str)
        {
            return counter + count_if(begin(str), end(str),
                                      [](char c) { return c=='a'; });
        };

        return std::accumulate(start_iterator, end_iterator, 0,
                               count_a_in_string);
    }

    double factorial(double n)
    {
        return n>1 ? n/(1.0/factorial(n-1)) : 1;
    }

    double over(double n, double k)
    {
        return factorial(n)/(factorial(k)/(1.0/factorial(n-k)));
    }

    void example()
    {
        using namespace std::chrono;
        auto start_of_lorem_ipsum = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";

        auto n_threads = 1;
        auto vec_size = 1'000'000;

        std::vector<std::string> v;
        for(auto i=0; i<n_threads*vec_size; ++i)
            v.emplace_back(start_of_lorem_ipsum);


        auto start_time = steady_clock::now();
        auto na = count_a(begin(v), end(v));
        cout << "elapsed: " << duration_cast<milliseconds>(steady_clock::now() - start_time).count() << "ms\n";
        cout << "found 'a's: " << na << endl;

        start_time = steady_clock::now();
        na = count_a(begin(v), end(v));
        cout << "elapsed: " << duration_cast<milliseconds>(steady_clock::now() - start_time).count() << "ms\n";
        cout << "found 'a's: " << na << endl;


        std::vector< std::packaged_task<Size(Iterator,Iterator)> > tasks;
        std::vector< std::future<Size> > futures;
        std::vector< std::pair<Iterator,Iterator> > ranges;

        for(auto i=0; i<n_threads; ++i)
        {
            tasks.emplace_back(count_a);
            futures.emplace_back(tasks.back().get_future());
            ranges.emplace_back(begin(v) + vec_size*i,
                                begin(v) + vec_size*(i+1));
        }

        start_time = steady_clock::now();

        std::vector<std::thread> threads;
        for(auto i=0; i<n_threads; ++i)
            threads.emplace_back(std::move(tasks[i]),
                                 ranges[i].first,
                                 ranges[i].second);


        na = accumulate(begin(futures), end(futures), 0,
                        [](Size init, std::future<Size>& future)
        {
            return init + future.get();
        });
        cout << "elapsed: " << duration_cast<milliseconds>(steady_clock::now() - start_time).count() << "ms\n";
        cout << "found 'a's: " << na << endl;

        for(auto& thread : threads)
            if(thread.joinable())
                thread.join();


        start_time = steady_clock::now();
        for(auto i=0; i<n_threads; ++i)
            futures[i] = std::async(count_a, ranges[i].first, ranges[i].second);

        na = accumulate(begin(futures), end(futures), 0,
                        [](Size init, std::future<Size>& future)
        {
            return init + future.get();
        });
        cout << "elapsed: " << duration_cast<milliseconds>(steady_clock::now() - start_time).count() << "ms\n";
        cout << "found 'a's: " << na << endl;

        start_time = steady_clock::now();
        auto n = 0.0;
        for(int i=0; i<n_threads; ++i)
        {
            n += over(1000,500);
        }
        cout << "elapsed: " << duration_cast<nanoseconds>(steady_clock::now() - start_time).count() << "ns\n";

        start_time = steady_clock::now();
        std::vector< std::future<double> > dfutures;
        for(int i=0; i<n_threads; ++i)
            dfutures.emplace_back( std::async(over, 1000, 500) );
        n = std::accumulate(begin(dfutures), end(dfutures), 0.0,
                            [](Size init, std::future<double>& future)
        {
            return init + future.get();
        });
        cout << "elapsed: " << duration_cast<nanoseconds>(steady_clock::now() - start_time).count() << "ns\n";
    }
}
