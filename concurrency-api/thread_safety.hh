#pragma once

#include <iostream>
#include <mutex>
#include <stack>
#include <thread>

namespace thread_safety
{
    template <class T>
    class Stack
    {
    public:
        const T& top() const
        {
            return data.top();
        }

        void push(const T& t)
        {
            data.push(t);
        }

        void pop()
        {
            data.pop();
        }

        std::size_t size() const
        {
            return data.size();
        }

        bool empty() const
        {
            return data.empty();
        }

    private:
        std::stack<T> data;
    };


    template <class T>
    class ThreadSafeStack
    {
    public:
        ThreadSafeStack() = default;

        ThreadSafeStack(const ThreadSafeStack& other)
        {
            std::lock_guard<std::mutex> lock(other.m);
            data = other.data;
        }

        ThreadSafeStack& operator=(const ThreadSafeStack&) = delete;

        void push(const T& value)
        {
            std::lock_guard<std::mutex> lock(m);
            data.push(value);
        }

        std::shared_ptr<T> pop()
        {
            std::lock_guard<std::mutex> lock(m);
            if(data.empty())
                return nullptr;
            const auto value = std::make_shared<T>(data.top());
            data.pop();
            return value;
        }

    private:
        std::stack<T> data;
        mutable std::mutex m;
    };


    std::mutex cout_mutex;
    void do_something(int value)
    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "value = " << value << std::endl;
    }

    void example()
    {
        ThreadSafeStack<int> stack;
        stack.push(1);
        stack.push(2);

        auto task = [&stack]
        {
            const auto value = stack.pop();
            if(value)
                do_something(*value);
//            if(!stack.empty())
//            {
//                const auto value = stack.top();
//                stack.pop();
//                do_something(value);
//            }
        };

        std::thread t1(task), t2(task);
        t1.join(); t2.join();
    }
}
