#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <functional>

#define DEBUG true

using number_t = int;
using table_t = std::vector<std::vector<number_t>>;

struct matrix
{
    size_t m_size;
    table_t m_data;

    matrix(size_t size);

    std::vector<number_t>& operator[](size_t index);
};

struct callbacks
{
    bool result;
    bool flag;

    number_t x;
    number_t z;
    number_t free;

    size_t i;
    size_t j;

    callbacks();

    std::function<void(size_t)> top_for_each(matrix& main_m, matrix& top_m, number_t current);

    std::function<void(size_t)> left_for_each(matrix& main_m, matrix& left_m, number_t current);

    std::function<void(size_t, size_t)> main(matrix& main_m, matrix& top_m, matrix& left_m, number_t current);

    std::function<void()> on_next();
};

std::istream& operator>>(std::istream& in, matrix& matrix);

std::ostream& operator<<(std::ostream& out, matrix& matrix);

bool find_position(matrix& main_m, matrix& top_m, matrix& left_m, number_t current);

void traverse(size_t size, std::function<void(size_t, size_t)> const& callback, std::function<void()> const& on_next = nullptr);

void for_each_rest(size_t size, size_t x, std::function<void(size_t)> const& callback);

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

matrix::matrix(size_t size): m_size(size)
{
    m_data = table_t(size, std::vector<number_t>(size, 0));
}

std::vector<number_t>& matrix::operator[](size_t index)
{
    return m_data[index];
}

callbacks::callbacks(): result(false), flag(false), x(0), z(0), free(0), i(0), j(0)
{
}

std::function<void(size_t)> callbacks::top_for_each(matrix& main_m, matrix& top_m, number_t current)
{
    return [&](size_t k)
    {
        const auto is_top_zero = top_m[k][j] == 0;
        const auto is_more_then_main = current > main_m[k][j];
        const auto is_main_zero = main_m[k][j] == 0;
        const auto is_x_less_top = x <= top_m[k][j];
        const auto is_i_k_eql = i == k;
        const auto left = is_top_zero && is_more_then_main && !is_main_zero;
        const auto right = !is_top_zero && is_x_less_top && !is_i_k_eql && is_main_zero;
        if (left || right)
        {
            flag = false;
            return;
        }
        if (main_m[k][j] == 0)
        {
            ++x;
        }
    };
}

std::function<void(size_t)> callbacks::left_for_each(matrix& main_m, matrix& left_m, number_t current)
{
    return [&](size_t k)
    {
        const auto is_left_zero = left_m[i][k] == 0;
        const auto is_more_then_main = current > main_m[i][k];
        const auto is_main_zero = main_m[i][k] == 0;
        const auto is_free_lest_left = free <= left_m[i][k];
        const auto is_j_k_eql = k == j;
        const auto left = is_left_zero && is_more_then_main && !is_main_zero;
        const auto right = !is_left_zero && is_free_lest_left && !is_j_k_eql && is_main_zero;
        if (left || right)
        {
            flag = false;
            return;
        }
        if (main_m[i][k] == 0)
        {
            ++free;
        }
    };
}

std::function<void(size_t, size_t)> callbacks::main(matrix& main_m, matrix& top_m, matrix& left_m, number_t current)
{
    return [&](size_t p, size_t q)
    {
        i = p;
        j = q;
        const auto is_main_zero_on_i = main_m[i][j] == 0;
        if (!is_main_zero_on_i || result)
        {
            return;
        }
        ++z;
        x = 0;
        for (size_t k = 0; k < i; ++k)
        {
            const auto is_main_zero_on_k = main_m[k][j] == 0;
            x += is_main_zero_on_k ? 1 : 0;
        }
        const auto is_top_zero_on_i = top_m[i][j] == 0;
        const auto is_x_positive = x > 0;
        const auto is_x_more_top = x > top_m[i][j];
        flag = !(is_top_zero_on_i && is_x_positive || is_x_more_top);
        if (flag)
        {
            for_each_rest(main_m.m_size, i, top_for_each(main_m, top_m, current));
        }
        free = z - 1;
        const auto is_left_zero_on_i = left_m[i][j] == 0;
        const auto is_free_positive = free > 0;
        const auto is_free_more_left = free > left_m[i][j];
        flag = is_left_zero_on_i && is_free_positive || is_free_more_left ? false : flag;
        {
            for_each_rest(main_m.m_size, j, left_for_each(main_m, left_m, current));
        }
        if (flag)
        {
            main_m[i][j] = current;
            result = true;
        }
    };
}

std::function<void()> callbacks::on_next()
{
    return [&]()
    {
        z = 0;
    };
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
    callbacks cb;
    const auto callback = cb.main(main_m, top_m, left_m, current);
    const auto on_next = cb.on_next();
    traverse(main_m.m_size, callback, on_next);
    return cb.result;
}

void traverse(size_t size, std::function<void(size_t, size_t)> const& callback, std::function<void()> const& on_next)
{
    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = 0; j < size; ++j)
        {
            callback(i, j);
        }
        if (on_next != nullptr)
        {
            on_next();
        }
    }
}

void for_each_rest(size_t size, size_t x, std::function<void(size_t)> const& callback)
{
    for (auto k = x; k < size; ++k)
    {
        callback(k);
    }
}
