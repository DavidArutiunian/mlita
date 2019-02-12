#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>

const int MAX = 100;

void fill(char f[MAX][MAX])
{
    for (int i = 0; i < MAX; ++i)
    {
        for (int j = 0; j < MAX; ++j)
        {
            f[i][j] = '.';
        }
    }
}

void read(char f[MAX][MAX], const char* path)
{
    std::ifstream infile(path);
    if (!infile)
    {
        return;
    }
    std::string line;
    std::getline(infile, line);
    int i = 0;
    while (std::getline(infile, line))
    {
        for (int j = 0; j < line.size(); ++j)
        {
            f[i + 1][j + 1] = line.at(j);
        }
        i++;
    }
}

void write(int count, const char* path)
{
    std::ofstream outfile(path);
    outfile << count;
}

void dfs(char f[MAX][MAX], int i, int j)
{
    if (f[i][j] == '#')
    {
        f[i][j] = '.';
        dfs(f, i + 1, j);
        dfs(f, i - 1, j);
        dfs(f, i, j + 1);
        dfs(f, i, j - 1);
    }
}

int main()
{
    int count = 0;
    char f[MAX][MAX];
    fill(f);
    read(f, "input.txt");
    for (int i = 0; i < MAX; ++i)
    {
        for (int j = 0; j < MAX; ++j)
        {
            if (f[i][j] == '#')
            {
                dfs(f, i, j);
                count++;
            }
        }
    }
    write(count, "output.txt");
}
