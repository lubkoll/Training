#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main(int argc, char *argv[])
{
    std::unordered_map<std::string, std::string> u = {
        {"RED","#FF0000"},
        {"GREEN","#00FF00"},
        {"BLUE","#0000FF"}
    };

    // Iterate and print keys and values of unordered_map
    for( const auto& n : u ) {
        std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
    }

    // Add two new entries to the unordered_map
    u["BLACK"] = "#000000";
    u["WHITE"] = "#FFFFFF";

    // Output values by key
    std::cout << "The HEX of color RED is:[" << u["RED"] << "]\n";
    std::cout << "The HEX of color BLACK is:[" << u["BLACK"] << "]\n";

    // It is a priori not clear in which situation std::map, resp. std::unordered_map perform better.
    // This also depends on the particular implementation, see i.e.
    // https://stackoverflow.com/questions/3902644/choosing-between-stdmap-and-stdunordered-map
}
