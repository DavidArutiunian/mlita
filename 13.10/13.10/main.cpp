/*
13.10. Абракадабра (7)
Строка s называется супрефиксом для строки t, если t начинается с s и заканчивается на s.
Например, «abra» является супрефиксом для строки «abracadabra». В частности, сама строка t
является своим супрефиксом. Супрефиксы играют важную роль в различных алгоритмах на
строках.
В этой задаче требуется решить обратную задачу поиска. Задан словарь, содержащий n слов t 1 ,
t 2 , …, t n и набор из m строк-образцов s 1 , s 2 , …, s m . Необходимо для каждой строки-образца из
заданного набора найти количество слов в словаре, для которых эта строка-образец является
супрефиксом.
Арутюнян Д.Р. ПС-23
Visual Studio 2019
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define DEBUG false

struct sample
{
    std::string value;
    size_t position;

    sample(std::string value, size_t position)
        : position(position)
        , value(std::move(value))
    {
    }
};

int main()
{
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    size_t dict_size = 0;
    input >> dict_size;
    std::vector<std::string> dict;
    dict.reserve(dict_size);
    size_t counter = dict_size;
    while (counter-- != 0)
    {
        std::string string;
        input >> string;
        std::string buffer;
        size_t i, j;
        for (i = 0, j = string.size() - 1; i < string.size(); ++i, --j)
        {
            buffer += string[i];
            buffer += string[j];
        }
        dict.push_back(buffer);
    }
    std::sort(dict.begin(), dict.end());

    size_t samples_size = 0;
    input >> samples_size;
    std::vector<sample> samples;
    samples.reserve(samples_size);
    counter = samples_size;
    while (counter-- != 0)
    {
        std::string string;
        input >> string;
        std::string buffer;
        size_t i, j;
        for (i = 0, j = string.size() - 1; i < string.size(); ++i, --j)
        {
            buffer += string[i];
            buffer += string[j];
        }
        samples.push_back(sample(buffer, samples_size - counter - 1));
    }
    std::sort(samples.begin(), samples.end(), [](sample& left, sample& right) {
        return left.value < right.value;
    });

    std::vector<size_t> results(samples.size(), 0);
    size_t i, j, k, l;
    bool index_found = false;
    bool word_found = false;
    for (i = 0, j = 0, k = 0, l = 0; i < samples_size; ++i)
    {
        j = k;
        index_found = false;
        while (dict[j] < samples[i].value)
        {
            ++j;
            if (j == dict.size())
            {
                break;
            }
        }
        k = j;
        for (; j < dict.size(); ++j)
        {
            auto substr = dict[j].substr(0, samples[i].value.size());
            if (samples[i].value == substr)
            {
                if (!index_found && samples[i].value != dict[j])
                {
                    index_found = true;
                    k = j;
                }
                ++l;
            }
            else
            {
                break;
            }
        }
        if (word_found && !index_found)
        {
            k = j;
        }
        results[samples[i].position] = l;
        ++i;
        for (; i < samples.size(); ++i)
        {
            if (samples[i].value == samples[i - 1].value)
            {
                results[samples[i].position] = l;
            }
            else
            {
                --i;
                break;
            }
        }
        l = 0;
    }

    for (auto result : results)
    {
        output << std::to_string(result) << std::endl;
        if (DEBUG)
        {
            std::cout << std::to_string(result) << std::endl;
        }
    }
}
