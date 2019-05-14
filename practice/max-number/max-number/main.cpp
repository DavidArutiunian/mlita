#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

#define DEBUG true

int main()
{
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    int size = 0;
    input >> size;

    std::string num;
    while (size-- > 0)
    {
        char ch;
        input >> ch;
        num += ch;
    }

    auto it = std::min_element(num.begin(), num.end());
    auto max_pos = std::distance(num.begin(), it) + 1;

    output << max_pos << std::endl;
    if (DEBUG)
    {
        std::cout << max_pos << std::endl;
    }
}
