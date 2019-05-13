/*
16.4. Сугробы на ЛЭП (9)
Служба электроснабжения проводит мониторинг уровня снега, лежащего на ЛЭП. Вся ЛЭП
разбивается на участки опорами. Если снег падает на некоторый интервал ЛЭП, то высота
снежного покрова на этом интервале увеличивается на высоту выпавшего снега. Снег также имеет
тенденцию таять на некотором участке трассы в результате оттепели, однако сугробов
отрицательной толщины быть нет может. Энергетикам крайне важно уметь узнавать суммарную
высоту снежного покрова на некоторых участках, чтобы определять вероятность обрыва проводов.
Ввод из файла INPUT.TXT. В первой строке находятся через пробел два числа: N – количество
опор (1 <=  N <= 10000) и M – количество команд (1 <=  M <= 50000). 
Команды бывают двух видов:
	1 L R S - на участок с L-й опоры по R-ю выпало S сантиметров снега;
	2 L R – запрос о высоте снега на участке от L-й опоры по R-ю.
Таяние снега показывает первый вид команды с отрицательным значением S. Опоры
нумеруются от 1 до N.
Вывод в файл OUTPUT.TXT. На каждый запрос (команду второго вида) требуется выводить
суммарную высоту снежного покрова, лежащего на проводах от L-й опоры по R-ю.
Арутюнян Давид ПС-23
Visual Studio 2019
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define DEBUG true

using number_t = long long;
using array_t = std::vector<number_t>;
using tree_t = array_t;
using adds_t = array_t;

class CTree
{
public:
    CTree(const array_t& a)
        : m_tree(tree_t(a.size() * 4, 0))
        , m_adds(m_tree)
    {
        Build(a, 1, 0, static_cast<number_t>(a.size() - 1));
    }

    number_t Sum(number_t v, number_t l, number_t r, number_t tl, number_t tr)
    {
        if (l > r)
        {
            return 0;
        }
        if (l == tl && r == tr)
        {
            return m_tree[v];
        }
        number_t tm = (tl + tr) / 2;
        number_t add = m_adds[v] * (r - l + 1);
        return Sum(v * 2, l, std::min(r, tm), tl, tm) + Sum(v * 2 + 1, std::max(l, tm + 1), r, tm + 1, tr) + add;
    }

    void Update(number_t v, number_t l, number_t r, number_t tl, number_t tr, number_t add)
    {
        if (l > r)
        {
            return;
        }
        m_tree[v] = m_tree[v] + add * (r - l + 1);
        if (tl == l && tr == r)
        {
            m_adds[v] += add;
            return;
        }
        number_t tm = (tl + tr) / 2;
        Update(v * 2, l, std::min(r, tm), tl, tm, add);
        Update(v * 2 + 1, std::max(l, tm + 1), r, tm + 1, tr, add);
    }

private:
    tree_t m_tree;
    adds_t m_adds;

    void Build(const array_t& a, number_t v, number_t tl, number_t tr)
    {
        if (tl == tr)
        {
            m_tree[v] = a[tl];
        }
        else
        {
            number_t tm = (tl + tr) / 2;
            Build(a, v * 2, tl, tm);
            Build(a, v * 2 + 1, tm + 1, tr);
            m_tree[v] = m_tree[v * 2] + m_tree[v * 2 + 1];
        }
    }
};

int main()
{
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    number_t N = 0;
    input >> N;

    number_t M = 0;
    input >> M;

    CTree tree(array_t(N, 0));

    while (M-- > 0)
    {
        number_t command;
        input >> command;

        if (command == 1)
        {
            number_t i = 0;
            number_t j = 0;
            number_t D = 0;
            input >> i >> j >> D;
            tree.Update(1, i - 1, j - 2, 0, N - 1, D);
        }
        if (command == 2)
        {
            number_t i = 0;
            number_t j = 0;
            input >> i >> j;
            auto sum = tree.Sum(1, i - 1, j - 2, 0, N - 1);
            output << sum << std::endl;
            if (DEBUG)
            {
                std::cout << sum << std::endl;
            }
        }
    }
}
