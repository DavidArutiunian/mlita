#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <algorithm>
#include <fstream>

#define DEBUG true

using frequency_t = std::map<char, int>;
using result_t = std::vector<std::string>;

frequency_t get_frequencies_of_chars(std::string const& word);

bool check_frequencies(frequency_t const& left, frequency_t const& right);

void sort_result(result_t& result);

std::size_t get_total_size(result_t const& result);

int main()
{
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    std::string base_word;
    input >> base_word;

    std::vector<std::string> words{};

    std::string temp;
    while (input >> temp)
    {
        words.emplace_back(temp);
    }
    const auto base_freqs = get_frequencies_of_chars(base_word);

    result_t result;
    for (auto&& word : words)
    {
        auto freqs = get_frequencies_of_chars(word);
        if (check_frequencies(freqs, base_freqs))
        {
            result.push_back(word);
        }
    }

    sort_result(result);
    const auto sum = get_total_size(result);

    if (DEBUG)
    {
        std::cout << sum << std::endl;
    }
    output << sum << std::endl;

    for (auto&& string : result)
    {
        if (DEBUG)
        {
            std::cout << string << "\t\t" << string.size() << std::endl;
        }
        output << string << "\t\t" << string.size() << std::endl;
    }
}

std::size_t get_total_size(result_t const& result)
{
    std::size_t sum = 0;
	for (auto&& string : result)
	{
		sum += string.size();
	}
    return sum;
}

void sort_result(result_t& result)
{
    std::sort(
        result.begin(),
        result.end(),
        [](std::string const& first, std::string const& second)
        {
            return first.size() > second.size() || (first.size() == second.size() && first > second);
        }
    );
}

frequency_t get_frequencies_of_chars(std::string const& word)
{
    std::map<char, int> result;
    for (auto&& value : word)
    {
        result[value]++;
    }
    return result;
}

bool check_frequencies(frequency_t const& left, frequency_t const& right)
{
    for (auto&& pair : left)
    {
        if (right.find(pair.first) == right.end())
        {
            return false;
        }
        if (pair.second > right.at(pair.first))
        {
            return false;
        }
    }
    return true;
}
