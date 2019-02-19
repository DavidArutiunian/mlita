#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

constexpr int MAX = 200;

void read(int f[MAX][MAX], const char* path, std::pair<int, int>& dimensions);

std::vector<std::string> split(const std::string& s, const char delimiter);

template <typename T>
void write(T message, const char* path);

int min(const int x, const int y);

void min_cost(int cost[MAX][MAX], int dynamics[MAX][MAX], int m, int n);

int main()
{
    std::pair<int, int> dimensions;
	int cost[MAX][MAX] = {0};
	int dynamics[MAX][MAX] = {0};
    read(cost, "input.txt", dimensions);
    min_cost(cost, dynamics, dimensions.first, dimensions.second);
    std::cout << dynamics[dimensions.first - 1][dimensions.second - 1] << std::endl;
}

void read(int f[MAX][MAX], const char* path, std::pair<int, int>& dimensions)
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

int min(const int x, const int y)
{
    if (x < y)
    {
		return x;
    }
	return y;
}

void min_cost(int cost[MAX][MAX], int dynamics[MAX][MAX], const int m, const int n)
{
    if (n < 0 || m < 0)
    {
		return;;
    }
    if (m == 0 && n == 0) 
	{
		return;
    }
    for (auto i = 0; i < m; i++)
    {
        for (auto j = 0; j < n; j++)
        {
			dynamics[i][j] = min(i ? dynamics[i-1][j] : 0, j ? dynamics[i][j - 1] : 0) + cost[i][j];
        }
    }
}
