#include <iostream>

using std::cout;
using std::endl;


enum ErrorCode { NO_ERROR=1, FATAL_ERROR };

enum class SaferErrorCode
{
    UNKNOWN=0,  // to avoid problems with default-constructed error-codes,
                // i.e. when one forgets to mock functions in the google test framework,
                // better avoid '0' as error code
    NONE,
    FATAL
};

int main()
{
    auto error = ErrorCode();
    int value = error;
    cout << error << endl;

    auto safe_error = SaferErrorCode::NONE;
    auto safe_error2 = SaferErrorCode(2);
    cout << static_cast<int>(safe_error) << endl;
    cout << static_cast<int>(safe_error2) << endl;

    // error codes with the google test framework:
    // functions for which mocking is not specified provide default-constructed return values
}
