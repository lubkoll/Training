#pragma once

#include <thread>
#include <type_traits>

// Join/Detach threads on all paths.
class ThreadRAII
{
public:
    enum class DtorAction { join, detach };

    template <class... Args,
/*              class =
                typename std::enable_if<
                    std::is_constructible<std::thread,Args&&...>::value
                  >::type>
*/
              typename std::enable_if<
                    std::is_constructible<std::thread,Args&&...>::value
                >::type* = nullptr>
    ThreadRAII(DtorAction a, Args&&... args)
        : action(a),
          t(std::forward<Args>(args)...)
    {}

    ThreadRAII(DtorAction a, std::thread&& t)
        : action(a),
          t(std::move(t))
    {}

    ThreadRAII(ThreadRAII&&) = default;

    ThreadRAII& operator=(ThreadRAII&&) = default;

    ~ThreadRAII()
    {
        if (t.joinable()) {
            if (action == DtorAction::join) {
                t.join();
            } else {
                t.detach();
            }
        }
    }

    std::thread& get()
    {
        return t;
    }

private:
    DtorAction action;
    std::thread t;
};
