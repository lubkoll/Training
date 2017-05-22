#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

int main()
{
    using namespace std::chrono;

    vector<string> v;
    const string start_of_lorem_ipsum = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed pellentesque consequat purus ut fringilla. Morbi pharetra odio purus, eu viverra leo accumsan non. Vivamus nec metus nec nibh faucibus commodo. Aliquam quis ipsum egestas ante facilisis rhoncus ut nec nisi. Nulla quis tortor imperdiet, varius nibh nec, egestas nulla. Nullam porttitor interdum lacinia. Sed cursus eros a tortor malesuada, id commodo nunc condimentum. Suspendisse vel lacinia erat. Nunc malesuada sapien eu erat venenatis, ut laoreet justo congue. Suspendisse eu lacus ante. Cras vel tempor ligula.";

    constexpr auto n = 1'000'000;    

    auto start_time = system_clock::now();

    for(auto i=0; i<n; ++i)
        v.push_back(start_of_lorem_ipsum);

    auto end_time = system_clock::now();
    const auto duration = end_time - start_time;
    auto elapsed = duration_cast<milliseconds>(duration);
    cout << "elapsed time: " << elapsed.count() << " ms\n\n";


    start_time = system_clock::now();

    vector<string> w;
    w.reserve(n);

    for(auto i=0; i<n; ++i)
        w.emplace_back(start_of_lorem_ipsum);

    elapsed = duration_cast<milliseconds>(system_clock::now() - start_time);
    cout << "elapsed time: " << elapsed.count() << " ms\n\n";

    end_time = system_clock::now();
    std::cout << "time since epoch: " << end_time.time_since_epoch().count() << std::endl;

    // only with system clock
    auto time = system_clock::to_time_t(end_time);
    std::cout << std::put_time(localtime(&time), "%c %Z") << std::endl;

    // available clocks:
    // - system_clock
    // - steady_clock
    // - high_resolution_clock
}
