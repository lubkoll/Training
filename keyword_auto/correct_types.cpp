#include "correct_types.hh"
using namespace std;

void use_correct_types()
{
    cout << "Part I - Correct types" << endl;
    cout << "\tHelps in avoiding usage of wrong types that support implicit conversion.\n" << endl;
    vector<int> vec;
    {
        PRINT( int size = vec.size(); )
        print( "Is 'int' correct: ",
               is_same<int,decltype(vec.size())>::value );
    }
    {
        PRINT( unsigned size = vec.size(); )
        print( "Is 'unsigned' correct: ",
               is_same<unsigned,decltype(vec.size())>::value );
    }

    // Correct before auto:
    {
        PRINT( vector<int>::size_type size = vec.size(); )
        print( "Is 'vector<int>::size_type' correct: ",
               is_same<vector<int>::size_type,decltype(vec.size())>::value );
    }

    // Correct with auto:
    {
        PRINT( auto size = vec.size(); )
        print( "Is 'auto' correct: ",
               is_same<decltype(size),decltype(vec.size())>::value );
    }





    cout << "\n\tAnother subtle example.\n";
    cout << "\tIllustrates avoidance of redundant copies due to implicit conversion.\n\n";
    {
        unordered_map<int,int> map;
        map[0] = 0;

        cout << "\tLooks good:\n";
        PRINT( for( const pair<int,int>& entry : map ) {
            // do something
        } )

        cout << "\n\t... but is wrong, leading to an unintended copy for each key-value-pair in map:\n";
        print( "Is 'const pair<int,int>&' the correct type: ",
                is_same<   const pair<int,int>&,
                           decltype( *cbegin(map) )   >::value, "" );

        print( "Is 'const pair<const int,int>&' the correct type: ",
                is_same<   const pair<const int,int>&,
                           decltype( *cbegin(map) )         >::value );


        cout << "\n\tThus better write the for loop as:\n";
        PRINT( for( const auto& entry : map ) {  } );
        for( const auto& entry : map ) {
            print( "Is 'const auto&' the correct type: ",
                    is_same<   decltype(entry),
                                    decltype( *cbegin(map) )   >::value );
        }
        cout << "\t which is more likely to be correct and is more generic since we don't commit to fixed types\n\n";


        cout << "\t...resp., with C++14 we can use decltype(auto):\n\n";
        PRINT( const auto& const_map = map;
                for( decltype(auto) entry : const_map) { } )
        for( decltype(auto) entry : const_map ) {
            print( "Is 'decltype(auto)' the correct type: ",
                    is_same<   decltype(entry),
                                    decltype( *cbegin(map) )   >::value );
        }
    }
}
