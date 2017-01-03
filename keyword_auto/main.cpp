#include <iostream>

#include "correct_types.hh"
#include "initialization.hh"
#include "unknown_types.hh"
#include "template_type_deduction.h"
#include "auto_type_deduction.h"
#include "auto_return_values.hh"
#include "cpp14_only.hh"


/**
 * @brief Introduction of auto variables
 *
 * Using auto as type specifier:
 *
 * 1. auto variables must be initialized -> no weird bugs due to uninitialized variables
 *
 * 2. avoids type-mismatches that can lead to efficiency and portability problems
 *
 * 3. leads to more generic code
 *
 * 4. less code repetition
 *
 * 5. less typing
 *
 * 6. be careful with auto in combination with braced initialization
 */


int main(int, char*[])
{
    std::cout << std::boolalpha << "\n";

    

//    use_correct_types();

    guarantees_initialization();

//    work_with_unknown_and_difficult_types();

//    template_type_deduction::example();

//    auto_type_deduction::example();

//    auto_return_values::example();

//    cpp14_only();
}
