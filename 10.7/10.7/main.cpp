/*
10.7. Симпсон Гомер (9)
Гомер Симпсон пожертвовал N долларов на распространение дисков с фильмами о себе.
Имеется 3 вида дисков, которые продаются по ценам C 1 , C 2 и C 3 долларов. Требуется купить как
можно больше дисков так, чтобы осталась неизрасходованной как можно меньшая сумма денег.
Арутюнян Д.Р. ПС-23
Visual Studio 2017
*/

#include "pch.h"

#define DEBUG false

using t_number = long long;
using t_prices = std::vector<t_number>;
using t_disc = std::vector <t_number>;
using t_discs = std::vector<t_disc>;

const std::size_t PRICE_LINE_COUNT = 3;

inline void read(t_number& balance, t_prices& prices);

inline void write(t_number balance, t_discs const& discs);

inline void process(t_number& balance, t_prices& prices, t_discs& discs);

inline t_number get_sum_of_discs(t_discs const& discs);

inline void set_discs(std::vector<t_number> const& actual_prices, t_prices const& prices, t_discs& discs);

inline t_discs restore_initial_sort(t_prices const& initial_prices, t_discs const& discs);

enum position
{
    first = 0,
    second,
    third
};

enum disc
{
	position = 0,
	price
};

int main()
{
    try
    {
        t_number balance = 0;
        t_prices prices{};
        t_discs discs{};
        read(balance, prices);
        const auto initial_prices(prices);
        std::sort(prices.begin(), prices.end());
        process(balance, prices, discs);
        write(balance, restore_initial_sort(initial_prices, discs));
        
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
}

void process(t_number& balance, t_prices& prices, t_discs& discs)
{
    for (std::size_t i = 0; i < prices.size() - 1; ++i)
    {
		const auto all = balance / prices[i];
		const auto div = (prices[i + 1] - prices[i]);
        if (div == 0)
        {
			continue;
        }
		const auto first = (balance - all * prices[i]) / div;
		const auto second = all - first;
        if (all == 0 && first == 0 && second == 0)
        {
			continue;
        }
		const auto third = all - (second + first);
		balance = balance - (second * prices[i] + first * prices[i + 1]);
		set_discs({ second, first, third }, prices, discs);
    }
}

void read(t_number& balance, t_prices& prices)
{
    std::fstream input("input.txt");
    input >> balance;
    for (std::size_t i = 0; i < PRICE_LINE_COUNT; ++i)
    {
        prices.emplace_back(0);
        input >> prices.back();
    }
}

void write(const t_number balance, t_discs const& discs)
{
    std::ofstream output("output.txt");
    output << get_sum_of_discs(discs) << std::endl;
    if (DEBUG)
    {
        std::cout << get_sum_of_discs(discs) << std::endl;
    }
    output << balance << std::endl;
    if (DEBUG)
    {
        std::cout << balance << std::endl;
    }
    for (auto&& disc : discs)
    {
        output << disc[price] << ' ';
        if (DEBUG)
        {
            std::cout << disc[price] << ' ';
        }
    }
    output << std::endl;
    if (DEBUG)
    {
        std::cout << std::endl;
    }
}

t_number get_sum_of_discs(t_discs const& discs)
{
    t_number sum = 0;
    for (auto&& disc : discs)
    {
        sum += disc[price];
    }
    return sum;
}

void set_discs(std::vector<t_number> const& actual_prices, t_prices const& prices, t_discs& discs)
{
	discs.clear();
	discs.push_back({ prices[first], actual_prices[first] });
	discs.push_back({ prices[second], actual_prices[second] });
	discs.push_back({ prices[third], actual_prices[third] });
}

t_discs restore_initial_sort(t_prices const& initial_prices, t_discs const& discs)
{
    t_discs discs_initial_sort{};
    auto discs_copy(discs);
    for (std::size_t i = 0; i < discs_copy.size(); ++i)
    {
        if (initial_prices[i] == discs_copy[i][position])
        {
			discs_initial_sort.push_back(discs_copy[i]);
        } else
        {
            for (auto j = i; j < discs_copy.size(); ++j)
            {
                if (initial_prices[i] == discs_copy[j][position])
                {
					discs_initial_sort.push_back(discs_copy[j]);
					std::swap(discs_copy[j], discs_copy[j - 1]);
                }
            }
        }
    }
    return discs_initial_sort;
}
