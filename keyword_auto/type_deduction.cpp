#include "type_deduction.hh"

const auto max_spacing = 36u;
const char print_indent[] = "\t\t";
#include "../util/util.hh"

using namespace std;

template <class T, int N>
constexpr int array_size(T(&)[N] )
{
    return N;
}

void foo()
{
    cout << "foo" << endl;
}


void type_deduction()
{
    cout << "\tauto type deduction is (almost) template type deduction\n\n";
   {
       PRINT( auto a = 0; )
       print( "Type specifier of a:\t" + QUALIFIER( a ) );

       PRINT( const auto b = a; )
       print( "Type specifier of b:\t" + QUALIFIER( b ) );

       PRINT( const auto& c = a; )
       print( "Type specifier of c:\t" + QUALIFIER( c ) );

       print( "Copy: const, volatile and references are discarded." );
       print( "Same behaviour as with template arguments that are taken by value." );
       PRINT( auto d = c; )
       print( "Type specifier of d:\t" + QUALIFIER( d ) );

       print( "Reference: retain const" );
       PRINT( auto& e = c; )
       print( "Type specifier of e:\t" + QUALIFIER( e ) );
   }


   cout << "\nSome less known cases of template/auto type deduction:\n";
   {
       cout << "\n\tArray-to-Pointer Decay\n";
       PRINT( const char name[] = "Scott Meyers"; )

       PRINT( auto a = name; )
       print( "Type of a is 'const char*'",
               is_same< decltype(a),
                             const char* >::value );

       PRINT( auto& b = name; );
       print( "Type of b is 'const char(&)[13]'",
               is_same< decltype(b),
                             const char(&)[13] >::value );

       // We can write a function to get the size of an array
       cout << "\n\t\tSize of array \"" << name << "\": " << array_size(name) << endl;


       cout << "\n\tFunction Pointers and References" << endl;
       PRINT( auto func1 = foo; )
       print( "Type of func1 is 'void(*)()'",
               is_same< decltype(func1),
                             void(*)()        >::value );
       PRINT( auto& func2 = foo; )
       print( "Type of func2 is 'void(&)()'",
               is_same< decltype(func2),
                             void(&)()        >::value );
   }

}
