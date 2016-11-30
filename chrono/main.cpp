#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace std::chrono;

int main()
{
    vector<string> v;
    string start_of_lorem_ipsum = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed pellentesque consequat purus ut fringilla. Morbi pharetra odio purus, eu viverra leo accumsan non. Vivamus nec metus nec nibh faucibus commodo. Aliquam quis ipsum egestas ante facilisis rhoncus ut nec nisi. Nulla quis tortor imperdiet, varius nibh nec, egestas nulla. Nullam porttitor interdum lacinia. Sed cursus eros a tortor malesuada, id commodo nunc condimentum. Suspendisse vel lacinia erat. Nunc malesuada sapien eu erat venenatis, ut laoreet justo congue. Suspendisse eu lacus ante. Cras vel tempor ligula.";


    constexpr auto n = 1'000'000;

    // least efficent at startup
    auto start_time = system_clock::now();

    for(auto i=0; i<n; ++i)
        v.push_back(start_of_lorem_ipsum);

    time_point<system_clock> end_time = system_clock::now();
    auto elapsed = duration_cast<milliseconds>(end_time - start_time);
    cout << "elapsed time: " << elapsed.count() << " ms\n\n";

    // most efficient
    vector<string> w;
    w.reserve(n);
    start_time = system_clock::now();

    for(auto i=0; i<n; ++i)
        w.emplace_back(start_of_lorem_ipsum);

    end_time = system_clock::now();
    elapsed = duration_cast<milliseconds>(end_time - start_time);
    cout << "elapsed time: " << elapsed.count() << " ms\n\n";

    // less efficient
    vector<string> z;
    start_time = system_clock::now();

    for(auto i=0; i<n; ++i)
        z.push_back(start_of_lorem_ipsum);

    end_time = system_clock::now();
    elapsed = duration_cast<milliseconds>(end_time - start_time);
    cout << "elapsed time: " << elapsed.count() << " ms\n\n";

    cout << "milliseconds since 1.1.1970: " << end_time.time_since_epoch().count() << endl;

    // to/from_time_t only exists for std::system_clock,
    // not for std::steady_clock or std::high_resolution_clock
    auto time = system_clock::to_time_t(end_time);
    cout << "time: " << put_time(localtime(&time), "%c %Z") << endl;
}
