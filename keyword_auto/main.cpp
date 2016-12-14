#include <iostream>

//#include "correct_types.hh"
//#include "initialization.hh"
//#include "unknown_types.hh"
//#include "type_deduction.hh"
//#include "difference_between_auto_and_type_deduction.hh"
//#include "cpp14_only.hh"






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
 */


int main(int, char*[])
{
    std::cout << std::boolalpha << "\n";

    auto x = 3;

//    use_correct_types();

//    guarantees_initialization();

//    work_with_unknown_types();

//    type_deduction();

//    difference_between_auto_and_type_deduction();

//    cpp14_only();

}
