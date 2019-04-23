#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

#define DEBUG true

using row_t = std::vector<int>;
using matrix_t = std::vector<row_t>;

struct virus
{
    size_t x;
    size_t y;
    int priority;
};

int main()
{
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    size_t size = 0;
    size_t count = 0;
    input >> size >> count;
    size += 2;
    int priority = static_cast<int>(size * size) + 1;

    matrix_t matrix(size, row_t(size, priority));
    for (size_t i = 0; i < size; ++i)
    {
        matrix[0][i] = 1;
        matrix[size - 1][i] = 1;
        matrix[i][0] = 1;
        matrix[i][size - 1] = 1;
    }
    std::queue<virus> queue{};

    size_t x = 0;
    size_t y = 0;
    while (input >> x >> y)
    {
        queue.push({ x, y });
    }

    while (!queue.empty())
    {
        auto current = queue.front();
        queue.pop();
        auto next_priority = current.priority + 1;
        if (next_priority < matrix[current.y + 1][current.x])
        {
            queue.push({ current.x, current.y + 1, next_priority });
            matrix[current.y + 1][current.x] = next_priority;
        }
        if (next_priority < matrix[current.y - 1][current.x])
        {
            queue.push({ current.x, current.y - 1, next_priority });
            matrix[current.y - 1][current.x] = next_priority;
        }
        if (next_priority < matrix[current.y][current.x + 1])
        {
            queue.push({ current.x + 1, current.y, next_priority });
            matrix[current.y][current.x + 1] = next_priority;
        }
        if (next_priority < matrix[current.y][current.x - 1])
        {
            queue.push({ current.x - 1, current.y, next_priority });
            matrix[current.y][current.x - 1] = next_priority;
        }
    }

    int max = 0;
    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = 0; j < size; ++j)
        {
            if (matrix[i][j] > max)
            {
                max = matrix[i][j];
            }
        }
    }

    output << max << std::endl;
    if (DEBUG)
    {
        std::cout << max << std::endl;
    }
}
