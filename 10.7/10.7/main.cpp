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
using t_discs = std::unordered_map<t_number, t_number>;

const std::size_t PRICE_LINE_COUNT = 3;

inline void read(t_number& balance, t_prices& prices);

inline void write(t_number balance, t_discs const& discs);

inline void process(t_number& balance, t_prices& prices, t_discs& discs);

inline t_number get_sum_of_discs(t_discs const& discs);

inline void set_discs(std::vector<t_number> const& actual_prices, t_prices const& prices, t_discs& discs);

inline t_discs restore_initial_sort(t_prices const& prices, t_discs& discs);

enum position
{
    first = 0,
    second,
    third
};

int main()
{
    try
    {
        t_number balance = 0;
        t_prices prices{};
        t_discs discs{};
        read(balance, prices);
        const t_prices initial_prices(prices);
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
    const auto min_price = *std::min_element(prices.begin(), prices.end());
    const auto initial_balance = balance;
    if (balance % min_price == 0)
    {
        discs[min_price] = initial_balance / min_price;
    }
    for (auto i = initial_balance / min_price; i > 0; --i)
    {
        t_number second_price = 0;
        while (initial_balance - min_price * i >= second_price * prices[second])
        {
            t_number third_price = 0;
            const auto local_second = initial_balance - min_price * i - second_price * prices[second];
            if (local_second >= 0 && local_second < balance)
            {
                balance = local_second;
                set_discs({i, second_price, third_price}, prices, discs);
            }
            while (local_second >= (third_price * prices[third]))
            {
                const auto local_third = initial_balance - min_price * i - second_price * prices[second] - third_price * prices[third];
                if (local_third >= 0 && local_third < balance)
                {
                    balance = local_third;
                    set_discs({i, second_price, third_price}, prices, discs);
                }
                ++third_price;
                if (balance == 0)
                {
                    return;
                }
            }
            ++second_price;
            if (balance == 0)
            {
                return;
            }
        }
        if (balance == 0)
        {
            return;
        }
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
        output << disc.second << ' ';
        if (DEBUG)
        {
            std::cout << disc.second << ' ';
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
        sum += disc.second;
    }
    return sum;
}

void set_discs(std::vector<t_number> const& actual_prices, t_prices const& prices, t_discs& discs)
{
    discs[prices[first]] = actual_prices[first];
    discs[prices[second]] = actual_prices[second];
    discs[prices[third]] = actual_prices[third];
}

t_discs restore_initial_sort(t_prices const& prices, t_discs& discs)
{
    t_discs buffer{};
    buffer[prices[first]] = discs[prices[first]];
    buffer[prices[second]] = discs[prices[second]];
    buffer[prices[third]] = discs[prices[third]];
    return buffer;
}
