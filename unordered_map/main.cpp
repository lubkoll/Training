#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main()
{
    // Create hash map of using
    // std::initializer_list< std::pair<std::string,std::string> > and std::pair's aggregate initialization
    std::unordered_map<std::string, std::string> u = {
        {"RED","#FF0000"},
        {"GREEN","#00FF00"},
        {"BLUE","#0000FF"}
    };

    // Range-based for-loop to print keys and values
    for( const auto& n : u ) {
        std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
    }

    // Add two new entries
    u["BLACK"] = "#000000";
    u["WHITE"] = "#FFFFFF";

    // Output values by key
    std::cout << "The HEX of color RED is:[" << u["RED"] << "]\n";
    std::cout << "The HEX of color BLACK is:[" << u["BLACK"] << "]\n";

    // It is a priori not clear in which situation std::map, resp. std::unordered_map perform better.
    // This also depends on the particular implementation, see i.e.
    //  - https://stackoverflow.com/questions/3902644/choosing-between-stdmap-and-stdunordered-map
}
