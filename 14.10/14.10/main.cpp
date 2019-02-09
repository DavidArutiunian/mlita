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
#include "btree.h"
#include <algorithm>

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

std::pair<int, int> to_params(const std::string& string)
{
    auto tokens = split(string, ' ');
    return {std::stoi(tokens[0]), std::stoi(tokens[1])};
}

template <typename T>
void write(T message, const std::string& path)
{
    std::ofstream outfile(path);
    outfile << message;
}

void split_wood(const int key, const std::unique_ptr<btree> & tree)
{
	if (key == 0)
	{
		return;
	}


	tree->insert(key);

    const auto prev_left = key;
    const auto left = key / 2;
    const auto right = prev_left - std::max(left, 1);

	split_wood(left, tree);
	split_wood(right, tree);
}

int main()
{
    try
    {
        const std::unique_ptr<btree> tree(new btree);
        auto result = 0;
        const auto input = read("input.txt");
        const auto params = to_params(input);
		tree->insert(params.first);
		tree->insert(params.first - params.second);
		split_wood(params.second, tree);
        const auto root = static_cast<node*>(tree->get_root());
        btree::traverse(root, [&params, &result](node* node)
        {
            if (node->value == params.first)
            {
                return;
            }
            result += node->value;
        });
        write(result, "output.txt");
    }
    catch (std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
}
