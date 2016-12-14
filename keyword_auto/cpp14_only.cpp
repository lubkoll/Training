#include "cpp14_only.hh"

const auto max_spacing = 36u;
const char print_indent[] = "\t\t";
#include "../util/util.hh"

using namespace std;

void cpp14_only()
{
    {
        cout << "\tThat's it for C++11, but not for C++14.\n";
        cout << "\tDoes not compile:\n";
        PRINT_ONLY( auto create_initializer_list()
                    {
                        return { 1 };
                    } );

        cout << endl;
        print( "In C++14 auto can be used for return types (without trailing '->')." );
        print( "Though, in this case, template type deduction rules are applied." );
        print( "Consequently initializer_list can not be deduced.\n" );

        cout << "\tC++14 only: decltype(auto)\n";
        cout << "\tUse auto with decltype type-deduction rules\n\n";
        PRINT( decltype(auto) a = 1; );
        print( "Type of a is 'int'",
                is_same< int, decltype(a) >::value );

        PRINT( decltype(auto) b = a; );
        print( "Type of b is 'int'",
               is_same< int, decltype(b) >::value );

        PRINT( auto& c = a; );
        PRINT( decltype(auto) d = c; );
        print( "Type of d is 'int&'",
               is_same< int&, decltype(d) >::value );

        PRINT( const auto& e = a; );
        PRINT( decltype(auto) f = e; );
        print( "Type of f is 'const int&'",
               is_same< const int&, decltype(f) >::value );

        PRINT( decltype(auto) g = std::move(a); );
        print( "Type of g is 'int&&'",
               is_same< int&&, decltype(g) >::value );

        cout << "\tYou cannot move from const variables:\n";
        PRINT( const auto vec = vector<int>(2,1); );
        PRINT( decltype(auto) wec = move(vec); );
        print( "Type of wec is 'const std::vector<int>&&'",
               is_same< const vector<int>&&, decltype(wec) >::value );
        print( "Size of vec", vec.size(), "" );
        print( "Size of wec", wec.size(), "" );
        print( "Const forwarding references will trigger the copy constructor, not the move constructor.\n" );

        print( "Generic lambda also use template type deduction rules: ");
        PRINT( auto lessThan = []( const auto& x, const auto& y )
                               {
                                   return x < y;
                               }; );

        cout << endl;
    }
}

