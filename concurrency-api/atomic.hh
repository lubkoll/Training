#pragma once

#include <atomic>
#include <functional>
#include <future>
#include <iostream>

namespace atomic
{
    void write_hello()
    {
        std::cout << "hello" << std::endl;
    }

    void count_executions_in_all_threads(std::atomic<int>& counter,
                                         std::function<void()> f)
    {
        f();
        ++counter;
    }

    void example()
    {
        std::atomic<int> counter{0};
        auto function = [&counter]
        {
            count_executions_in_all_threads(counter, write_hello);
        };

        auto future_1 = std::async(std::launch::async, function);
        auto future_2 = std::async(std::launch::async, function);

        future_1.get();
        future_2.get();
        std::cout << "executions: " << counter << "\n\n";
    }
}
