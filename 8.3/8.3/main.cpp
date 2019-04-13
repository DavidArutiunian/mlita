#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#define DEBUG true

using number_t = int;
using table_t = std::vector<std::vector<number_t>>;

struct matrix
{
    size_t m_size;
    table_t m_data;

    matrix(size_t size) : m_size(size)
    {
        m_data = table_t(size, std::vector<number_t>(size, 0));
    }

    std::vector<number_t>& operator[](size_t index)
    {
        return m_data[index];
    }
};

std::istream& operator>>(std::istream& in, matrix& matrix);

std::ostream& operator<<(std::ostream& out, matrix& matrix);

bool find_position(matrix& main_m, matrix& top_m, matrix& left_m, number_t current);

int main()
{
    try
    {
        std::ifstream input("input.txt");
        std::ofstream output("output.txt");
        size_t size = 0;
        input >> size;
        matrix top(size);
        input >> top;
        matrix left(size);
        input >> left;
        matrix main(size);

        bool error = false;

        for (size_t i = 0; i <= size * size; ++i)
        {
            auto current = static_cast<number_t>(i);
            if (!find_position(main, top, left, current))
            {
                error = true;
                break;
            }
        }

        if (error)
        {
            output << 0 << std::endl;
            if (DEBUG)
            {
                std::cout << 0 << std::endl;
            }
        }
        else
        {
            output << main;
        }
    }
    catch (std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
}

std::istream& operator>>(std::istream& in, matrix& matrix)
{
    for (size_t i = 0; i < matrix.m_size; ++i)
    {
        for (size_t j = 0; j < matrix.m_size; ++j)
        {
            in >> matrix[i][j];
        }
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, matrix& matrix)
{
    for (size_t i = 0; i < matrix.m_size; ++i)
    {
        for (size_t j = 0; j < matrix.m_size; ++j)
        {
            out << matrix[i][j] << ' ';
            if (DEBUG)
            {
                std::cout << matrix[i][j] << ' ';
            }
        }
        out << std::endl;
        if (DEBUG)
        {
            std::cout << std::endl;
        }
    }
    return out;
}

bool find_position(matrix& main_m, matrix& top_m, matrix& left_m, number_t current)
{
    const auto size = main_m.m_size;
    auto x = 0;
    auto z = 0;
    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = 0; j < size; ++j)
        {
            if (main_m[i][j] == 0)
            {
                ++z;
                x = 0;
                for (size_t k = 0; k < i; ++k)
                {
                    x += main_m[k][j] == 0 ? 1 : 0;
                }
                auto flag = !(top_m[i][j] == 0 && x > 0 || x > top_m[i][j]);
                if (flag)
                {
                    for (auto k = i; k < size; ++k)
                    {
                        const auto left = top_m[k][j] == 0 && current > main_m[k][j] && main_m[k][j] != 0;
                        const auto right = top_m[k][j] != 0 && x <= top_m[k][j] && i != k && main_m[k][j] == 0;
                        if (left || right)
                        {
                            flag = false;
                            break;
                        }
                        if (main_m[k][j] == 0)
                        {
                            ++x;
                        }
                    }
                }
                auto free = z - 1;
                flag = left_m[i][j] == 0 && free > 0 || free > left_m[i][j] ? false : flag;
                {
                    for (auto k = j; k < size; ++k)
                    {
                        const auto left = left_m[i][k] == 0 && current > main_m[i][k] && main_m[i][k] != 0;
                        const auto right = left_m[i][k] != 0 && free <= left_m[i][k] && k != j && main_m[i][k] == 0;
                        if (left || right)
                        {
                            flag = false;
                            break;
                        }
                        if (main_m[i][k] == 0)
                        {
                            ++free;
                        }
                    }
                }
                if (flag)
                {
                    main_m[i][j] = current;
                    return true;
                }
            }
        }
        z = 0;
    }
    return false;
}
