#include "difference_between_auto_and_type_deduction.hh"

const auto max_spacing = 36u;
const char print_indent[] = "\t\t";
#include "../util/util.hh"

using namespace std;

void difference_between_auto_and_type_deduction()
{
    cout << "A difference between template and auto type deduction\n";
    {
        cout << "\tC++98 initialization:\n";
        PRINT( int a( 0 ); );
        PRINT( int b = 0; );
        cout << endl;
    }

    {
        cout << "\tC++11 uniform initialization:\n";
        PRINT( int c{ 0 }; );
        PRINT( int d = { 0 }; );
        cout << endl;
    }

    {
        cout << "\tReplace types with auto:\n";
        PRINT( auto a( 0 ); );
        print( "Type of a is 'int'",
               is_same< int, decltype(a) >::value );
        cout << endl;

        PRINT( auto b = 0; );
        print( "Type of b is 'int'",
               is_same< int, decltype(b) >::value );
        cout << endl;

        PRINT( auto c{ 0 }; );
        print( "Type of c is 'std::initializer_list<int>'",
               is_same< std::initializer_list<int>, decltype(c) >::value );
        cout << endl;

        PRINT( auto d = { 0 }; );
        print( "Type of d is 'int'",
               is_same< int, decltype(d) >::value, "" );
        print( "Type of d is 'initializer_list<int>'",
               is_same< initializer_list<int>, decltype(d) >::value );

        cout << "\t\tThis is different from template type deduction, which never will deduce a initializer_list\n\n";
        // @TODO Add explanation
    }
}

