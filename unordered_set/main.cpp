#include <iostream>
#include <unordered_set>

struct Point {
    int x, y;
};

bool operator==(const Point& x, const Point& y)
{
    return x.x == y.x && x.y == y.y;
}

namespace std
{
    template<> struct hash<Point>
    {
        typedef Point argument_type;
        typedef std::size_t result_type;
        result_type operator()(argument_type const& s) const
        {
            return std::hash<int>()(s.x) ^ std::hash<int>()(s.y);
        }
    };
}

int main() {
    // Create unordered set of (unique!) elements using
    // std::initializer_list<Point> and Point's aggregate initialization
    std::unordered_set<Point> points = {
        {1, 42},
        {1, 73},
        {1, 42}
    };

    // Range-based for loop to print points
    for (const auto& point : points) {
        std::cout << "(" << point.x << ", " << point.y << ")" << std::endl;
    }
}
