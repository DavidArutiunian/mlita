#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#define DEBUG true

using coordinate_t = std::pair<size_t, size_t>;
using coordinates_t = std::vector<coordinate_t>;
using results_t = std::vector<bool>;

results_t get_results(const coordinates_t& start);

bool process(coordinate_t const& start);

std::istream& operator>>(std::istream& in, coordinates_t& coordinates);

std::ostream& operator<<(std::ostream& out, results_t const& results);

int main()
{
    try
    {
        std::ifstream input("input.txt");
        std::ofstream output("output.txt");

        coordinates_t coordinates;
        input >> coordinates;

        const auto results = get_results(coordinates);

        output << results;
        if (DEBUG)
        {
            std::cout << results;
        }
    }
    catch (std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
}

results_t get_results(const coordinates_t& start)
{
    results_t result;
    for (const auto coordinate : start)
    {
        auto is_first_win = process(coordinate);
        result.emplace_back(is_first_win);
    }
    return result;
}

bool process(coordinate_t const& start)
{
    return !(start.first % 2 && start.second % 2);
}

std::istream& operator>>(std::istream& in, coordinates_t& coordinates)
{
    auto count = 0;
    in >> count;
    while (count > 0)
    {
        count--;
        size_t x = 0;
        size_t y = 0;
        in >> x;
        in >> y;
        coordinates.push_back(std::make_pair(x, y));
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, results_t const& results)
{
    for (const auto result : results)
    {
        const auto winner = result ? '1' : '2';
        out << winner << std::endl;
    }
    return out;
}
