#include "constexpr_.hh"
#include "default_and_delete.hh"
#include "final_and_override.hh"
#include "noexcept_.hh"

int main()
{
    constexpr_example();
    noexcept_example();
    default_and_delete_example();
    final_and_override_example();
}
