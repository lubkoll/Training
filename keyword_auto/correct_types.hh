#pragma once

#include <iostream>
#include <map>
#include <type_traits>
#include <vector>

using namespace std;

void use_correct_types()
{
    // auto helps in avoiding usage of wrong types that support implicit conversion
    vector<int> vec;
    int size = vec.size();
    unsigned usize = vec.size();

    {
        cout << "std::is_same<int, decltype(vec.size())>::value = "
             << std::is_same<int, decltype(vec.size())>::value << endl;
    }
    {
        cout << "std::is_same<unsigned, decltype(vec.size())>::value = "
             << std::is_same<unsigned, decltype(vec.size())>::value << endl;
    }

    // Correct before auto:
    {
        vector<int>::size_type size = vec.size();
        cout << "std::is_same<vector<int>::size_type, decltype(vec.size())>::value = "
             << std::is_same<vector<int>::size_type, decltype(vec.size())>::value << endl;
    }

    // Correct with auto:
    {
        auto size = vec.size();
        cout << "std::is_same<decltype(size), decltype(vec.size())>::value = "
             << std::is_same<decltype(size), decltype(vec.size())>::value << endl;
    }



    cout << "\n\tAnother subtle example.\n";
    cout << "\tIllustrates avoidance of redundant copies due to implicit conversion.\n\n";
    {
        map<int,int> mymap;
        mymap[0] = 0;

        // Looks good:
        for( const pair<int,int>& entry : mymap ) {
            // do something
        }



        // ... but is wrong, leading to an unintended copy for each key-value-pair in mymap
        cout << "std::is_same<const pair<int,int>&, decltype( *cbegin(mymap) )>::value = "
             << std::is_same< const pair<int,int>&,
                              decltype( *cbegin(mymap) ) >::value << endl;

        cout << "std::is_same<const pair<const int,int>&, decltype( *cbegin(mymap) )>::value = "
             << std::is_same< const pair<const int,int>&,
                              decltype( *cbegin(mymap) ) >::value << endl;


        // Thus better write the for loop as
        for( const auto& entry : mymap ) {
            // do something
        }

        cout << "std::is_same<const pair<const int,int>&, decltype( *cbegin(mymap) )>::value = "
             << std::is_same< const pair<const int,int>&,
                              decltype( *cbegin(mymap) ) >::value << endl;
        for( const auto& entry : mymap ) {
            print( "Is 'const auto&' the correct type: ",
                    is_same<   decltype(entry),
                                    decltype( *cbegin(mymap) )   >::value );
        }
        cout << "\t which is more likely to be correct and is more generic since we don't commit to fixed types\n\n";


        cout << "\t...resp., with C++14 we can use decltype(auto):\n\n";
        PRINT( const auto& const_map = mymap;
                for( decltype(auto) entry : const_map) { } )
        for( decltype(auto) entry : const_map ) {
            print( "Is 'decltype(auto)' the correct type: ",
                    is_same<   decltype(entry),
                                    decltype( *cbegin(mymap) )   >::value );
        }
    }
}
