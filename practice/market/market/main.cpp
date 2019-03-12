#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>

int main()
{
    try
    {
        std::ifstream input("input.txt");
        std::string line;

        auto N = 0;
        auto M = 0;
        input >> N >> M;

        std::getline(input, line);
        line.clear();

        std::vector<long long> sellers;
        sellers.reserve(N);
        std::getline(input, line);

        {
            std::stringstream ss(line);
            std::string token;
            while (std::getline(ss, token, ' '))
            {
                sellers.emplace_back(std::stoi(token));
            }
        }

        std::vector<long long> consumers;
        consumers.reserve(M);
        std::getline(input, line);

        {
            std::stringstream ss(line);
            std::string token;
            while (std::getline(ss, token, ' '))
            {
                consumers.emplace_back(std::stoi(token));
            }
        }


        std::sort(sellers.begin(), sellers.end());
        std::sort(consumers.begin(), consumers.end());

        long long max_cost = LONG_MIN;
        long long total_max_price = LONG_MIN;

        auto sellers_pos = 0;
        auto consumers_pos = 0;

        auto positive_sellers = 0;
        auto positive_consumers = 0;


        for (std::size_t i = 0; i < consumers.size(); ++i)
        {
            const auto max_price = consumers[i];

            for (std::size_t j = sellers_pos; j < sellers.size(); ++j)
            {
                const auto seller = sellers[j];
                if (seller <= max_price)
                {
                    sellers_pos++;
                    positive_sellers++;
                }
                else
                {
                    break;
                }
            }

            for (std::size_t j = consumers_pos; j < consumers.size(); ++j)
            {
                const auto consumer = consumers[j];
                if (consumer >= max_price)
                {
                    consumers_pos++;
                    positive_consumers++;
                }
                else
                {
                    break;
                }
            }
            int total_positive_consumers = positive_consumers - i;

            const auto min_people = std::min(positive_sellers, total_positive_consumers);

            const auto next_max_cost = max_price * min_people;
            if (next_max_cost > max_cost)
            {
                total_max_price = max_price;
                max_cost = next_max_cost;
            }
        }

        std::cout << total_max_price << ' ' << max_cost << std::endl;
    }
    catch (std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
}
