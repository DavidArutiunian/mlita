#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

struct point
{
    int x;
    int type;

    point(const int x, const int type) : x(x), type(type)
    {
    }

    point()
    {
        x = 0;
        type = 0;
    }
};

inline bool comp(const point a, const point b)
{
    return a.x < b.x || a.x == b.x && a.type > b.type;
}

int main()
{
    try
    {
        std::ifstream file("input.txt");
        auto m = 0;
        auto n = 0;
        file >> m >> n;
        auto res = 0;
        auto count = 0;
        std::vector<point> points(2 * m);
        for (auto j = 0; j < m; ++j)
        {
            auto x = 0;
            auto y = 0;
            file >> x >> y;
            points[2 * j] = point(x, 1);
            points[2 * j + 1] = point(y, -1);
        }
        std::sort(points.begin(), points.end(), comp);
        auto entered = false;
        for (auto& point : points)
        {
            res += point.type;
            if (res > n - 1 && !entered)
            {
                entered = true;
                count++;
            }
            if (res <= n - 1 && entered)
            {
                entered = false;
            }
        }
        std::cout << count << std::endl;
    }
    catch (std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
}
