#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>

#define DEBUG false

const int MAX = 10;

void fill(char f[MAX][MAX])
{
	for (auto i = 0; i < MAX; ++i)
	{
		for (auto j = 0; j < MAX; ++j)
		{
			f[i][j] = '.';
		}
	}
}

void copy(char from[MAX][MAX], char to[MAX][MAX])
{
	for (auto i = 0; i < MAX; ++i)
	{
		for (auto j = 0; j < MAX; ++j)
		{
			to[i][j] = from[i][j];
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
    auto i = 0;
	while (std::getline(infile, line))
	{
		for (std::size_t j = 0; j < line.size(); ++j)
		{
			f[i + 1][j + 1] = line.at(j);
		}
		i++;
	}
}

void write(const int count, const char* path)
{
	std::ofstream outfile(path);
	outfile << count;
}

void dfs(char f[MAX][MAX], const int i, const int j, int &max_count, int count = 0)
{
	char buffer[MAX][MAX];
	copy(f, buffer);
	if (buffer[i][j] == '#')
	{
		count++;
		buffer[i][j] = '.';
		dfs(buffer, i + 1, j, max_count, count);
		dfs(buffer, i - 1, j, max_count, count);
		dfs(buffer, i, j + 1, max_count, count);
		dfs(buffer, i, j - 1, max_count, count);
	}
    if (count > max_count)
    {
		max_count = count;
    }
}

int main()
{
	try
	{
		auto max_count = 0;
		char f[MAX][MAX];
		fill(f);
		read(f, "input.txt");
		for (auto i = 0; i < MAX; ++i)
		{
		    for (auto j = 0; j < MAX; ++j)
			{
				if (f[i][j] == '#')
				{
					dfs(f, i, j, max_count);
				}
			}
		}
		write(max_count, "output.txt");
        if (DEBUG)
        {
			std::cout << max_count << std::endl;
        }
	} catch (std::exception &ex)
	{
		std::cerr << ex.what() << std::endl;
	}
}
