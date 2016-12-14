#include "unknown_types.hh"

const auto max_spacing = 36u;
const char print_indent[] = "\t\t";
#include "../util/util.hh"

using namespace std;

void work_with_unknown_types()
{
    cout << "\nPart III - Unknown types\n";
    cout << "\tThe type of lambda expressions is only known to the compiler.\n" <<
            "\tStoring in an auto declared variable is more efficient and more convenient than in a function object:\n";
    PRINT( auto a = [] (int x)
    {
        return 2*x;
    };
            );
    print( "Type of a is 'int(*)(int)'",
           is_same< decltype(a),
           void(*)()        >::value );
    cout << endl;
}
