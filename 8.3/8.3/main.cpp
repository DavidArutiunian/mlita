/*
8.3. Матрица (8)
В матрице A размера NN числа от 1 до N 2 . Каждое число записано ровно один раз. Даны две
матрицы размера NN: Top и Left. Значение Top i j определяет количество чисел, больших A i j и
расположенных выше по столбцу, Left i j - количество чисел, больших A i j и расположенных левее по
строке. Найти возможные значения матрицы A. Если решений несколько, вывести любое.
Арутюнян Давид ПС-23
Visual Studio 2019
*/

#include <vector>
#include <iostream>
#include <fstream>

#define DEBUG false

using number_t = int;
using table_t = std::vector<std::vector<number_t>>;

struct matrix
{
    size_t m_size;
    table_t m_data;

    matrix(size_t size);

    std::vector<number_t>& operator[](size_t index);
};

std::istream& operator>>(std::istream& in, matrix& matrix);

std::ostream& operator<<(std::ostream& out, matrix& matrix);

int main()
{
    try
    {
        std::ifstream input("input.txt");
        std::ofstream output("output.txt");
        size_t size = 0;
        input >> size;
        matrix top_m(size);
        input >> top_m;
        matrix left_m(size);
        input >> left_m;
        matrix main_m(size);

        bool error = false;

        for (size_t i = 0; i < top_m.m_size; ++i)
        {
            for (size_t j = 0; j < top_m.m_size; ++j)
            {
                const auto top_more_i = static_cast<size_t>(top_m[i][j]) > i;
                const auto left_more_j = static_cast<size_t>(left_m[i][j]) > j;
                if (top_more_i || left_more_j)
                {
                    error = true;
                    break;
                }
            }
            if (error)
            {
                break;
            }
        }

        if (!error)
        {
            for (size_t i = 0; i <= size * size; ++i)
            {
                auto current = static_cast<number_t>(i);
                bool result = false;
                bool flag = false;
                number_t x = 0;
                number_t z = 0;
                number_t free = 0;
                for (size_t j = 0; j < main_m.m_size; ++j)
                {
                    for (size_t m = 0; m < main_m.m_size; ++m)
                    {
                        const auto is_main_zero_on_i = main_m[j][m] == 0;
                        if (!is_main_zero_on_i)
                        {
                            continue;
                        }
                        ++z;
                        x = 0;
                        for (size_t k = 0; k < j; ++k)
                        {
                            const auto is_main_zero_on_k = main_m[k][m] == 0;
                            x += is_main_zero_on_k ? 1 : 0;
                        }
                        const auto is_top_zero_on_i = top_m[j][m] == 0;
                        const auto is_x_positive = x > 0;
                        const auto is_x_more_top = x > top_m[j][m];
                        flag = !(is_top_zero_on_i && is_x_positive || is_x_more_top);
                        if (flag)
                        {
                            for (auto k = j; k < main_m.m_size; ++k)
                            {
                                const auto is_top_zero = top_m[k][m] == 0;
                                const auto is_more_then_main = current > main_m[k][m];
                                const auto is_main_zero = main_m[k][m] == 0;
                                const auto is_x_less_top = x <= top_m[k][m];
                                const auto is_i_k_eql = j == k;
                                const auto left = is_top_zero && is_more_then_main && !is_main_zero;
                                const auto right = !is_top_zero && is_x_less_top && !is_i_k_eql && is_main_zero;
                                if (left || right)
                                {
                                    flag = false;
                                    break;
                                }
                                if (main_m[k][m] == 0)
                                {
                                    ++x;
                                }
                            }
                        }
                        free = z - 1;
                        const auto is_left_zero_on_i = left_m[j][m] == 0;
                        const auto is_free_positive = free > 0;
                        const auto is_free_more_left = free > left_m[j][m];
                        flag = is_left_zero_on_i && is_free_positive || is_free_more_left ? false : flag;
                        if (flag)
                        {
                            for (auto k = m; k < main_m.m_size; ++k)
                            {
                                const auto is_left_zero = left_m[j][k] == 0;
                                const auto is_more_then_main = current > main_m[j][k];
                                const auto is_main_zero = main_m[j][k] == 0;
                                const auto is_free_lest_left = free <= left_m[j][k];
                                const auto is_j_k_eql = k == m;
                                const auto left = is_left_zero && is_more_then_main && !is_main_zero;
                                const auto right = !is_left_zero && is_free_lest_left && !is_j_k_eql && is_main_zero;
                                if (left || right)
                                {
                                    flag = false;
                                    break;
                                }
                                if (main_m[j][k] == 0)
                                {
                                    ++free;
                                }
                            }
                        }
                        if (flag)
                        {
                            main_m[j][m] = current;
                            result = true;
                            break;
                        }
                    }
                    if (result)
                    {
                        break;
                    }
                    z = 0;
                }
                if (!result)
                {
                    error = true;
                    break;
                }
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
            output << main_m;
        }
    }
    catch (std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
}

matrix::matrix(size_t size): m_size(size)
{
    m_data = table_t(size, std::vector<number_t>(size, 0));
}

std::vector<number_t>& matrix::operator[](size_t index)
{
    return m_data[index];
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
