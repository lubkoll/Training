#pragma once

#include <future>
#include <iostream>

namespace future_and_promise
{
    void write()
    {
        std::cout << "Finished waiting.\n";
    }

    void signals(std::promise<void> promise)
    {
        std::this_thread::sleep_for(1ms); // 'std::literals::1s' available in C++14

        std::cout << "Notifying threads...\n";
        promise.set_value();
    }


    void simple_future_example()
    {
        // A pattern to start one thread and suspend it until a one-shot signal is triggered
        // std::promise can only be used once, for other than one-shot events use std::condition_variable.
        std::promise<void> promise;
        std::thread t1( [future = promise.get_future()] // C++14
                        { future.wait();
                          write(); } ),
                    t2(signals, std::move(promise));
        t1.join();
        t2.join();
        std::cout << "\n";
    }


    void second_signals(std::promise<void> promise)
    {
        std::this_thread::sleep_for(1ms); // 'std::literals::1s' available in C++14

        std::cout << "Notifying threads...\n";
        promise.set_value();
        std::this_thread::sleep_for(100ms);
    }

    void shared_future_example()
    {
        // A pattern to start an arbitrary number of threads and suspend it until a one-shot signal is triggered
        std::promise<void> promise;
        auto shared_future = promise.get_future().share();
        std::thread t1( [shared_future]{ shared_future.wait();
                                         write(); } ),
                    t2( [shared_future]{ shared_future.wait();
                                         write(); } ),
                    t3( [shared_future]{ shared_future.wait();
                                         write(); } ),
                    t4(second_signals, std::move(promise));

        t1.join();
        t2.join();
        t3.join();
        t4.join();
        std::cout << "\n";
    }


    void packaged_task_example()
    {
        // Prepare 'normal' function for asynchronous execution
        auto add_one = [](int i) { return i + 1; };
        std::packaged_task<int(int)> task(add_one);

        // Get future for task result
        auto result = task.get_future();

        // Run task asynchronously
        std::thread t(std::move(task), 41);
        t.join();

        std::cout << "Packaged task result: " << result.get() << std::endl;
    }


    void example()
    {
        simple_future_example();
//        shared_future_example();
//        packaged_task_example();
        // Note:
        // The last future referring to a shared state for a non-deferred task
        // launched via std::async blocks until the task completes!
    }
}
