/*
7.3. Прямоугольники 1(8)
На координатной плоскости задано N прямоугольников со сторонами, параллельными
координатным осям. Найти площадь фигуры, получающейся в результате объединения
прямоугольников.
Ввод из файла INPUT.TXT. В первой строке содержится значение N (1 ≤ N ≤ 500). В каждой из
следующих N строк – четыре целых числа A i , B i , C i , D i через пробел, определяющие координаты
левого верхнего и правого нижнего углов очередного прямоугольника (-10 6 ≤ A i , B i , C i , D i ≤ 10 6 ; A i
≤ C i ; B i ≥ D i ).
Вывод в файл OUTPUT.TXT единственного целого числа – площади фигуры.
Пример
Ввод
2
5 15 25 5
0 10 20 0
Вывод
325
Арутюнян Д.Р.
Visual Studio 2017
*/

#include "pch.h"
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

struct rectangle
{
    double x1;
    double y1;
    double x2;
    double y2;
};

struct segment
{
    double a;
    double b;
};

std::istream& operator>>(std::istream& in, rectangle& rect)
{
    in >> rect.x1 >> rect.y1 >> rect.x2 >> rect.y2;
    return in;
}

int main()
{
    try
    {
        int count;
        std::cin >> count;
        std::vector<rectangle> rects;
        while (count-- > 0)
        {
            rects.push_back(rectangle{});
            std::cin >> rects.back();
        }

        std::vector<double> x_events;
        for (auto& rect : rects)
        {
            x_events.push_back(rect.x1);
            x_events.push_back(rect.x2);
        }
        std::sort(x_events.begin(), x_events.end());
        const auto it = std::unique(x_events.begin(), x_events.end());
        x_events.resize(std::distance(x_events.begin(), it));

        double area = 0;
        for (std::size_t i = 0; i < x_events.size() - 1; ++i)
        {
            const auto x = x_events[i];
            std::deque<double> start, end;
            for (auto& rect : rects)
            {
                if (rect.x1 <= x && rect.x2 > x)
                {
                    if (rect.y1 < rect.y2)
                    {
                        start.push_back(rect.y1);
                        end.push_back(rect.y2);
                    }
                    else
                    {
                        start.push_back(rect.y2);
                        end.push_back(rect.y1);
                    }
                }
            }
            std::sort(start.begin(), start.end());
            std::sort(end.begin(), end.end());

            auto depth = 0;
            segment seg{};
            std::vector<segment> segments;
            while (!start.empty() || !end.empty())
            {
                double y = 0;
                const auto pre_depth = depth;
                if (!start.empty() && start.front() <= end.front())
                {
                    depth++;
                    y = start.front();
                    start.pop_front();
                }
                else
                {
                    depth--;
                    y = end.front();
                    end.pop_front();
                }
                if (pre_depth == 0)
                {
                    seg.a = y;
                }
                else if (depth == 0)
                {
                    seg.b = y;
                    segments.push_back(seg);
                }
            }

            const auto width = x_events[i + 1] - x;
            for (auto& segment : segments)
            {
                area += width * (segment.b - segment.a);
            }
        }
        std::cout << area << std::endl;
    }
    catch (std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
}
