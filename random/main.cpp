#include <chrono>
#include <cmath>
#include <ctime>
#include <functional>
#include <iostream>
#include <random>

// Generate uniformly distributed integer numbers in [low,high].
// Each run of this program will generate the same sequence.
int rand_int(int low, int high)
{
    // random number generation engine (seeded with default value)
    static std::minstd_rand engine{};
    // random number distribution
    static std::uniform_int_distribution<int> distribution {};
    return distribution(engine,
                        std::uniform_int_distribution<int>::param_type{low, high});
}

// Generate uniformly distributed integer numbers in [low,high].
// Each run of this program will (probably) generate a different sequence.
int rand_int_seeded(int low, int high)
{
    using clock = std::chrono::system_clock;

    // seed random number engine with system time
    static auto seed = clock::from_time_t(std::time(nullptr)).time_since_epoch().count();
    // random number generation engine
    static std::minstd_rand engine(seed);
    // random number distribution
    static std::uniform_int_distribution<int> distribution {};

    return distribution(engine,
                        std::uniform_int_distribution<int>::param_type{low, high});
}

int main()
{
    std::cout << "uniform_int_distribution" << std::endl;
    for(auto i=0; i<10; ++i)
        std::cout << rand_int(42,73) << std::endl;
    std::cout << std::endl;

    std::cout << "uniform_int_distribution (seeded with current time)" << std::endl;
    for(auto i=0; i<10; ++i)
        std::cout << rand_int_seeded(42,73) << std::endl;
    std::cout << std::endl;

    std::cout << "normal_distribution (example of Stroustroup)" << std::endl;
    // random number generation engine (seeded with default value)
    std::default_random_engine re;   // the default engine
    // random number distribution
    std::normal_distribution<double> nd(31 /* mean */,8 /* sigma */);

    auto norm = std::bind(nd, re);

    std::vector<int> mn(64);
    for (int i = 0; i<1200; ++i) ++mn[std::round(norm())]; // generate

    for (int i = 0; i<mn.size(); ++i) {
        std::cout << i << '\t';
        for (int j=0; j<mn[i]; ++j) std::cout << '*';
        std::cout << '\n';
    }

    /**
     * Much more at:
     *  - http://en.cppreference.com/w/cpp/header/random
     *  - http://www.stroustrup.com/C++11FAQ.html#std-random
     */
}
