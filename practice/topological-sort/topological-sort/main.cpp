#include "pch.h"

#define DEBUG false

using t_result = std::vector<int>;
using t_used = std::vector<bool>;
using t_cl = std::vector<char>;
using t_graph = std::vector<std::vector<int>>;

void dfs(int value, t_graph& g, t_used& used, t_result& result);

void topological_sort(t_graph& graph, t_used& used, t_result& result);

bool is_cyclic(int value, int& cycle_st, int& cycle_end, t_graph& graph, t_cl& cl);

int main()
{
    try
    {
        std::ifstream input("input.txt");
        std::ofstream output("output.txt");
        auto n = 0;
        input >> n;
        t_graph graph(n);
        for (auto i = 0; i < n; ++i)
        {
            auto m = 0;
            input >> m;
            for (auto j = 0; j < m; ++j)
            {
                auto k = 0;
                input >> k;
                graph[k - 1].push_back(i);
            }
        }
        t_used used(graph.size(), false);
        t_result result{};
        t_cl cl{};
        auto cycle_st = -1;
        auto cycle_end = 0;
        cl.assign(n, 0);
        for (auto i = 0; i < n; ++i)
        {
            if (is_cyclic(i, cycle_st, cycle_end, graph, cl))
            {
                break;
            }
        }
        if (cycle_st != -1)
        {
            output << "NO" << std::endl;
            if (DEBUG)
            {
                std::cout << "NO" << std::endl;
            }
            return EXIT_SUCCESS;
        }
        topological_sort(graph, used, result);
        output << "YES" << std::endl;
        if (DEBUG)
        {
            std::cout << "YES" << std::endl;
        }
        for (auto&& value : result)
        {
            output << value + 1 << std::endl;
            if (DEBUG)
            {
                std::cout << value + 1 << std::endl;
            }
        }
    }
    catch (std::exception const& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    return EXIT_SUCCESS;
}

void dfs(const int value, t_graph& g, t_used& used, t_result& result)
{
    used[value] = true;
    for (size_t i = 0; i < g[value].size(); ++i)
    {
        const auto to = g[value][i];
        if (!used[to])
        {
            dfs(to, g, used, result);
        }
    }
    result.push_back(value);
}

void topological_sort(t_graph& graph, t_used& used, t_result& result)
{
    for (std::size_t i = 0; i < graph.size(); ++i)
    {
        if (!used[i])
        {
            dfs(i, graph, used, result);
        }
    }
    std::reverse(result.begin(), result.end());
}

bool is_cyclic(const int value, int& cycle_st, int& cycle_end, t_graph& graph, t_cl& cl)
{
    cl[value] = 1;
    for (size_t i = 0; i < graph[value].size(); ++i)
    {
        const auto to = graph[value][i];
        if (cl[to] == 0)
        {
            if (is_cyclic(to, cycle_st, cycle_end, graph, cl))
            {
                return true;
            }
        }
        else if (cl[to] == 1)
        {
            cycle_end = value;
            cycle_st = to;
            return true;
        }
    }
    cl[value] = 2;
    return false;
}
