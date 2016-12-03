#pragma once

#include <functional>
#include <future>
#include <iostream>

namespace launch_policy
{
    void write_hello()
    {
        std::cout << "hello" << std::endl;
    }

    auto count_executions_in_separate_threads(std::function<void()> f)
    {
        thread_local int counter = 0;
        f();
        return ++counter;
    }

    void example()
    {
        // This may or may not be executed asynchronously, (if both counters are 1, open some tabs in your browser and try again)
        // since the default launch policy of std::async is
        // std::launch::async | std::launch::deferred
        auto future_1 = std::async(count_executions_in_separate_threads, write_hello);
        auto future_2 = std::async(count_executions_in_separate_threads, write_hello);

        // Until here, count_execution_in_separate_threads may not have been executed,
        // since execution may be deferred.
        auto counter1 = future_1.get();
        auto counter2 = future_2.get();
        std::cout << "counters: " << counter1 << ", " << counter2 << "\n\n";

        // Specify std::launch::async to guarantee asynchronous execution, only do this
        // when you are absolutely sure you need to.
        auto future_3 = std::async(std::launch::async,
                                   count_executions_in_separate_threads, write_hello);
        auto future_4 = std::async(std::launch::async,
                                   count_executions_in_separate_threads, write_hello);

        // Blocking access to results as soon as parallel execution has terminated.
        auto counter3 = future_3.get();
        auto counter4 = future_4.get();
        std::cout << "counters: " << counter3 << ", " << counter4 << "\n\n";
    }
}
