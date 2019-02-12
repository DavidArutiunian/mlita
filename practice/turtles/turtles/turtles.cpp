#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

constexpr int MAX = 200;

void read(int** f, const char* path, std::pair<int, int>& dimensions);

std::vector<std::string> split(const std::string& s, const char delimiter);

template <typename T>
void write(T message, const char* path);

void* allocate_memory(const std::pair<int, int>& dimensions);

void* reallocate_memory(int** f, const std::pair<int, int>& dimensions);

void free_memory(int** f, const std::pair<int, int>& dimensions);

int min(int x, int y, int z);

int min_cost(int** cost, int m, int n);

int main()
{
    // Чтение исходных данных
    std::pair<int, int> dimensions;
    auto f = static_cast<int **>(allocate_memory({MAX, MAX}));
    read(f, "input.txt", dimensions);
    f = static_cast<int **>(reallocate_memory(f, dimensions));

    const auto cost = min_cost(f, dimensions.first - 1, dimensions.second - 1);

    std::cout << cost << std::endl;

    // Освобождение памяти
    free_memory(f, dimensions);
}

void read(int** f, const char* path, std::pair<int, int>& dimensions)
{
    std::ifstream infile(path);
    if (!infile)
    {
        return;
    }
    std::string line;
    std::getline(infile, line);
    auto splitted = split(line, ' ');
    dimensions.first = std::stoi(splitted[0]);
    dimensions.second = std::stoi(splitted[1]);
    auto i = 0;
    while (std::getline(infile, line))
    {
        splitted = split(line, ' ');
        for (auto j = 0; j < splitted.size(); ++j)
        {
            f[i][j] = std::stoi(splitted.at(j));
        }
        i++;
    }
}

std::vector<std::string> split(const std::string& s, const char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream stream(s);
    while (std::getline(stream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

template <typename T>
void write(T message, const char* path)
{
    std::ofstream outfile(path);
    outfile << message;
}

void* allocate_memory(const std::pair<int, int>& dimensions)
{
    const auto f = static_cast<int **>(calloc(MAX, sizeof(int *)));
    for (auto i = 0; i < MAX; i++)
    {
        f[i] = static_cast<int *>(calloc(MAX, sizeof(int)));
    }
    return f;
}

void* reallocate_memory(int** f, const std::pair<int, int>& dimensions)
{
    const auto m = static_cast<int **>(realloc(f, dimensions.first * sizeof(int *)));
    for (auto i = 0; i < dimensions.first; i++)
    {
        m[i] = static_cast<int *>(realloc(f[i], dimensions.second * sizeof(int)));
    }
    return m;
}

void free_memory(int** f, const std::pair<int, int>& dimensions)
{
    for (auto i = 0; i < dimensions.first; i++)
    {
        free(f[i]);
    }
    free(f);
}

int min(int x, int y, int z)
{
    if (x < y)
        return (x < z) ? x : z;
    else
        return (y < z) ? y : z;
}

int min_cost(int** cost, int m, int n)
{
    if (n < 0 || m < 0)
        return std::numeric_limits<int>::min();
    else if (m == 0 && n == 0)
        return cost[m][n];
    else
        return cost[m][n] + min(
            min_cost(cost, m - 1, n - 1),
            min_cost(cost, m - 1, n),
            min_cost(cost, m, n - 1)
        );
}
