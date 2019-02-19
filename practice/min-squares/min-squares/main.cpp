#include "pch.h"
#include <iostream>
#include <algorithm>
#include <vector>

int min_squares(const int size);

int main()
{
    auto input = 0;
    std::cin >> input;
    std::cout << min_squares(input) << std::endl;
}

int min_squares(const int size)
{
    std::vector<int> path(size + 1);
    std::vector<int> dynamics(size + 1);

    for (auto i = 0; i <= size; i++)
    {
        dynamics[i] = i;

        for (auto j = 0; j <= i; j++)
        {
            const auto square = j * j;
            if (square > i)
            {
                break;
            }
            const auto prev = i - square;
            auto left = dynamics[i];
            auto right = 1 + dynamics[prev];
            const auto min = std::min(left, right);
            if (min < left)
            {
                path[i] = i - prev;
            }
            dynamics[i] = min;
        }
    }

    const auto result = dynamics[size];
	auto current = path[size];

    for (auto i = 0; i < result; i++)
    {
        if (!path[size - current * i] == 0)
        {
			current = path[size - current * i];
        }
		std::cout << std::sqrt(current) << ' ';
    }
    std::cout << std::endl;

    return result;
}
