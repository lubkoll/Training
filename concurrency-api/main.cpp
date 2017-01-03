#include "atomic.hh"
#include "condition_variables.hh"
#include "future_and_promise.hh"
#include "intro.hh"
#include "launch_policy.hh"
#include "raii_thread.hh"
#include "thread_safety.hh"

int main()
{
    intro::example();
    launch_policy::example();
    atomic::example();
    condition_variables::example();
    future_and_promise::example();
    thread_safety::example();

    // See
    // - Scott Meyers: Effective Modern C++, Items 35-40
    // - Anthony Williams: C++ Concurrency in Action: Practical Multithreading
}
