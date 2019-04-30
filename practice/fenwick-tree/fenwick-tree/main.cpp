#include <fstream>
#include <iostream>
#include <vector>

using number_t = int;
using array_t = std::vector<number_t>;
using tree_t = array_t;

void add(size_t i, number_t d, tree_t& tree)
{
    for (; i < tree.size(); i = (i | (i + 1)))
    {
        tree[i] += d;
    }
}

number_t rsq(number_t i, tree_t& tree)
{
    number_t result = 0;
    while (i >= 0)
    {
        result += tree[i];
        i = (i & (i + 1)) - 1;
    }
    return result;
}

number_t rsq(number_t i, number_t j, tree_t& tree)
{
    return rsq(i, tree) - rsq(j - 1, tree);
}

void print(tree_t& tree)
{
    for (size_t i = 0; i < tree.size(); ++i)
    {
        std::cout << rsq(static_cast<number_t>(i), static_cast<number_t>(i), tree) << ' ';
    }
    std::cout << std::endl;
}

int main()
{
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    size_t size = 0;
    input >> size;

    array_t array{};
    number_t x = 0;
    while (input >> x)
    {
        array.push_back(x);
    }

    tree_t tree(size, 0);

    for (size_t i = 0; i < tree.size(); ++i)
    {
        add(i, array[i], tree);
    }

    std::string token = "";

    while (token != "exit")
    {
        std::cout << ">> ";
        std::cin >> token;
        if (token == "add")
        {
            std::cout << "add >> ";
            number_t x, y;
            std::cin >> x >> y;
            add(x, y, tree);
        }
        else if (token == "rsq")
        {
            std::cout << "rsq >> ";
            number_t x, y;
            std::cin >> x >> y;
            std::cout << rsq(y, x, tree) << std::endl;
        }
        else if (token == "update")
        {
            std::cout << "update >> ";
            number_t x, y;
            std::cin >> x >> y;
            number_t a = rsq(x, x, tree);
            add(x, y - a, tree);
        }
        else if (token == "print")
        {
            print(tree);
        }
        else if (token == "clear")
        {
            system("cls");
        }
    }
}
