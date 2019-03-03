/*
4.8. Булева функция (7)
Недавно на уроке информатики ученики одного из классов изучили булевы функции.
Напомним, что булева функция f сопоставляет значениям двух булевых аргументов, каждый из
которых может быть равен 0 или 1, третье булево значение, называемое результатом. Для
учеников, которые выразили желание более подробно изучать эту тему, учительница информатики
на дополнительном уроке ввела в рассмотрение понятие цепного вычисления булевой функции f.
Если задана булева функция f и набор из N булевых значений a 1 , a 2 , ..., a N , то результат
цепного вычисления этой булевой функции определяется следующим образом:
* если N = 1, то он равен a 1 ;
* если N &gt; 1, то он равен результату цепного вычисления булевой функции f для набора из
(N–1) булевого значения f(a 1 ,a 2 ), a 3 , …, a N , который получается путем замены первых двух
булевых значений в наборе из N булевых значений на единственное булево значение –
результат вычисления функции f от a 1 и a 2 .
Например, если изначально задано три булевых значения: a 1 = 0, a 2 = 1, a 3 = 0, а функция f – ИЛИ
(OR), то после первого шага получается два булевых значения (0 OR 1) и 0, то есть 1 и 0. После
второго (и последнего) шага получается результат цепного вычисления, равный 1, так как
1 OR 0 = 1.
В конце дополнительного урока учительница информатики написала на доске булеву функцию
f и попросила одного из учеников выбрать такие N булевых значений a i , чтобы результат цепного
вычисления этой функции был равен единице. Более того, она попросила найти такой набор
булевых значений, в котором число единиц было бы как можно большим.
Требуется написать программу, которая решала бы поставленную учительницей задачу.
Использовать подход динамического программирования.
Ввод из файла INPUT.TXT. Первая строка содержит одно натуральное число N
(2 ≤ N ≤ 100 000). Вторая строка содержит описание булевой функции в виде четырех чисел,
каждое из которых – ноль или единица. Первое из них есть результат вычисления функции в
случае, если оба аргумента – нули, второе – результат в случае, если первый аргумент – ноль,
второй – единица, третье – результат в случае, если первый аргумент – единица, второй – ноль, а
четвертый – в случае, если оба аргумента – единицы.
Вывод в файл OUTUT.TXT. Необходимо вывести строку из N символов, определяющих
искомый набор булевых значений a i с максимально возможным числом единиц. Если ответов
несколько, требуется вывести любой из них. Если такого набора не существует, выведите в
выходной файл слово No.
Примеры
Ввод 1 Ввод 2 Ввод 3
4 5 6
0110 0100 0000
Вывод 1 Вывод 2 Вывод 3
1011 11111 No
Пояснения к примерам
В первом примере процесс вычисления цепного значения булевой функции f происходит
следующим образом:

1011 → 111 → 01 → 1

Во втором примере вычисление цепного значения булевой функции f происходит следующим
образом:
11111 → 0111 → 111 → 01 → 1
В третьем примере получить цепное значение булевой функции f, равное 1, невозможно.
Арутюнян Д.Р.
Visual Studio 2017
*/

#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

const auto MAX_N = 100000;
const auto MIN_N = 2;
const auto MAX_BOOLEAN_LENGTH = 4;

template <typename T>
void write(T message, const std::string& path);

inline int to_int(const char ch);

using array = std::vector<int>;
using row = array;
using table = std::vector<row>;

int main()
{
    try
    {
		std::ifstream input("input.txt");
		auto N = 0;
		input >> N;
        if (N < MIN_N || N > MAX_N)
        {
			throw std::invalid_argument("Argument is outside the range [" + std::to_string(MIN_N) + ";" + std::to_string(MAX_N) + "]!");
        }
		std::string boolean;
		input >> boolean;
        if (boolean.empty())
        {
			throw std::invalid_argument("Empty boolean description!");
        }
        if (boolean.length() > MAX_BOOLEAN_LENGTH)
        {
			throw std::invalid_argument("Descriptions must be 4 letters string!");
        }
		table dynamics(MAX_N, row(MIN_N));
		table methods(MAX_N, row(MIN_N));
		table results(MAX_N, row(MIN_N));
		dynamics[1][0] = 0;
		dynamics[1][1] = 1;
		results[1][0] = 0;
		results[1][1] = 1;
        for (auto i = MIN_N; i <= N; ++i)
        {
			dynamics[i][0] = -1;
			dynamics[i][1] = -1;
            for (auto j = 0; j <= 1; ++j)
            {
                for (auto k = 0; k <= 1; ++k)
                {
                    const auto b = to_int(boolean[j * 2 + k]);
                    if ((dynamics[i - 1][j] >= 0) && (dynamics[i][b] < dynamics[i - 1][j] + k)) {
						dynamics[i][b] = dynamics[i - 1][j] + k;
						methods[i][b] = j;
						results[i][b] = k;
                    }
                }
            }
        }
        if (dynamics[N][1] < 0)
        {
			write("No", "output.txt");
			return EXIT_SUCCESS;
        }
		array buffer(MAX_N, 0);
		auto j = 1;
        for (auto i = N; i >= 1; --i)
        {
			buffer[i] = results[i][j];
			j = methods[i][j];
        }
		array buffer_sliced(buffer.begin() + 1, buffer.begin() + N + 1);
		std::reverse(buffer_sliced.begin(), buffer_sliced.end());
        std::string message;
        for (auto i = 0; i <= N - 1; ++i)
        {
			message += std::to_string(buffer_sliced[i]);
        }
		write(message, "output.txt");
    } catch (std::exception &ex)
    {
		std::cerr << ex.what() << std::endl;
    }
}

int to_int(const char ch)
{
	return ch - '0';
}


template <typename T>
void write(T message, const std::string& path)
{
	std::ofstream outfile(path);
	outfile << message;
	outfile.close();
}
