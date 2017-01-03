#pragma once

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <thread>

using namespace std::literals;

namespace condition_variables
{
    std::condition_variable condition;
    std::mutex condition_mutex;
    std::atomic_bool flag{false};

    void waits()
    {
        std::unique_lock<std::mutex> lock(condition_mutex);
        std::cout << "Waiting... \n";
        condition.wait( lock,                        // wait and block thread
                        []{ return flag.load(); } );   // use condition to wake-up or to avoid spurious wake-ups
        std::cout << "...finished waiting.\n";
    }

    void signals()
    {
        std::this_thread::sleep_for(1ms); // '1s' available in C++14 in 'std::literals'
        std::cout << "Notifying falsely...\n";
        condition.notify_one(); // waiting thread is notified and continues waiting

        flag = true; // now notified thread is allowed to run
        std::this_thread::sleep_for(1ms);
        std::cout << "Notifying remaining threads...\n";
        condition.notify_all();
        std::this_thread::sleep_for(100ms);
    }

    void example()
    {
        std::thread t1(waits), t2(waits), t3(waits), t4(signals);
        t1.join();
        t2.join();
        t3.join();
        t4.join();
    }
}
