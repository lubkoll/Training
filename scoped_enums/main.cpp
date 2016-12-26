#include <iostream>

using std::cout;
using std::endl;


enum ErrorCode { NO_ERROR=0, FATAL_ERROR };

enum class SaferErrorCode { NO_ERROR=0, FATAL_ERROR };



bool do_something()
{
    return SaferErrorCode::NO_ERROR;
}


int main()
{
    auto error = ErrorCode();
    int value = error;
    cout << error << endl;

    auto err = do_something();
    if( err != SaferErrorCode::NO_ERROR ) {
        cout << "error\n";
    }

    auto safe_error = SaferErrorCode::NO_ERROR;
    auto safe_error2 = SaferErrorCode(2);
    cout << static_cast<int>(safe_error) << endl;
    cout << static_cast<int>(safe_error2) << endl;

    // error codes with the google test framework:
    // functions for which mocking is not specified provide default-constructed return values
}
