#include "atomic.hh"
#include "condition_variables.hh"
#include "future_and_promise.hh"
#include "launch_policy.hh"

int main()
{
    launch_policy::example();
    atomic::example();
    condition_variables::example();
    future_and_promise::example();
}
