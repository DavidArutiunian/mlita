/*
14.10. Распил бруса 2 (10)
На пилораму привезли брус длиной L метров. Требуется сделать N распилов. Распилы делят
брус на части, длина которых выражается натуральными числами. Стоимость одного распила
равна длине распиливаемого бруса. Определить минимальную стоимость распила.
Арутюнян Д.Р.
Visual Studio 2017
*/

#include "pch.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <queue>

// Чтение первой строки из файла
std::string read(const std::string& path);

// Разделение строки на вектор строк по символу разделителя
std::vector<std::string> split(const std::string& s, const char delimiter);

// Нормализация строки в параметры
std::pair<int, int> to_params(const std::string& string);

// Вывод сообщения в стандартный поток (файл)
template <typename T>
void write(T message, const std::string& path);


int main()
{
    try
    {
        const auto input = read("input.txt");
        const auto params = to_params(input);
		std::priority_queue<int, std::vector<int>, std::greater<>> queue;
		std::vector<int> parts;
        parts.reserve(params.second + 1);
        for (auto i = 0; i < params.second; i++)
        {
			parts.push_back(1);
			queue.push(1);
        }
		parts.push_back(params.first - params.second);
		queue.push(params.first - params.second);
        while (!queue.empty())
        {
            const auto left = queue.top();
			queue.pop();
            if (queue.empty())
            {
				break;
            }
            const auto right = queue.top();
			queue.pop();
			queue.push(left + right);
			parts.push_back(left + right);
        }
        auto sum = 0;
        for (auto && part : parts)
        {
            if (part == params.first)
            {
				continue;
            }
			sum += part;
        }
		std::cout << sum << std::endl;;
        write(sum, "output.txt");
    }
    catch (std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
}

template <typename T>
void write(T message, const std::string& path)
{
	std::ofstream outfile(path);
	outfile << message;
}

std::pair<int, int> to_params(const std::string& string)
{
	auto tokens = split(string, ' ');
	return { std::stoi(tokens[0]), std::stoi(tokens[1]) };
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

std::string read(const std::string& path)
{
	std::ifstream infile(path);
	if (!infile)
	{
		throw std::runtime_error("Cannot open the file " + path);
	}
	std::string line;
	std::getline(infile, line);
	return line;
}