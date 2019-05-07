#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

#define MAXN 100

int t[4 * MAXN];

void build(int a[], int v, int tl, int tr)
{
    if (tl == tr)
        t[v] = a[tl];
    else
    {
        int tm = (tl + tr) / 2;
        build(a, v * 2, tl, tm);
        build(a, v * 2 + 1, tm + 1, tr);
        t[v] = std::max(t[v * 2], t[v * 2 + 1]);
    }
}

int sum(int v, int tl, int tr, int l, int r)
{
    if (l > r)
        return 0;
    if (l == tl && r == tr)
        return t[v];
    int tm = (tl + tr) / 2;
    return std::max(
        sum(v * 2, tl, tm, l, std::min(r, tm)),
        sum(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r));
}

void update(int v, int tl, int tr, int pos, int new_val)
{
    if (tl == tr)
        t[v] += new_val;
    else
    {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v * 2, tl, tm, pos, new_val);
        else
            update(v * 2 + 1, tm + 1, tr, pos, new_val);
        t[v] = std::max(t[v * 2], t[v * 2 + 1]);
    }
}

void update(int v, int tl, int tr, int l, int r, int add)
{
    if (l > r)
        return;
    if (l == tl && tr == r)
        t[v] += add;
    else
    {
        int tm = (tl + tr) / 2;
        update(v * 2, tl, tm, l, std::min(r, tm), add);
        update(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r, add);
    }
}

int main()
{
    std::ifstream input("input.txt");

    int n = 0;
    input >> n;

    int array[MAXN];
    for (int i = 0; i < n; ++i)
    {
        int number;
        input >> number;
        array[i] = number;
    }
    build(array, 1, 0, n - 1);

    std::string token;
    while (token != "exit")
    {
        std::cout << ">> ";
        std::cin >> token;

        if (token == "add1")
        {
            int i = 0;
            int d = 0;
            std::cin >> i >> d;
            update(1, 0, n - 1, i - 1, d);
        }
        else if (token == "add2")
        {
            int i = 0;
            int j = 0;
            int d = 0;
            std::cin >> i >> j >> d;
            update(1, 0, n - 1, i - 1, j - 1, d);
        }
        else if (token == "rmq")
        {
            int i = 0;
            int j = 0;
            std::cin >> i >> j;
            std::cout << sum(1, 0, n - 1, i - 1, j - 1) << std::endl;
        }
    }
}
