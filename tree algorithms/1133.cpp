#include <iostream>
#include <vector>

using graph_t = std::vector<std::vector<size_t>>;
using integer = unsigned long long;

void traverse_1(const graph_t& g, size_t u, size_t p, std::vector<std::pair<unsigned, integer>>& v)
{
    for (const size_t x : g[u]) {
        if (x != p) {
            traverse_1(g, x, u, v);
            v[u].first += v[x].first;
            v[u].second += v[x].second + v[x].first;
        }
    }
}

void traverse_2(const graph_t& g, size_t u, size_t p, std::vector<std::pair<unsigned, integer>>& v)
{
    for (const size_t x : g[u]) {
        if (x != p) {
            v[x].second = v[u].second - 2 * v[x].first + v[u].first;
            v[x].first = v[u].first;
            traverse_2(g, x, u, v);
        }
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    graph_t g(n);
    for (size_t i = 0; i < n-1; ++i) {
        unsigned u, v;
        std::cin >> u >> v;

        g[u-1].push_back(v-1);
        g[v-1].push_back(u-1);
    }

    std::vector<std::pair<unsigned, integer>> v(n, std::make_pair(1, 0));
    traverse_1(g, 0, 0, v);
    traverse_2(g, 0, 0, v);

    for (size_t i = 0; i < n; ++i)
        std::cout << v[i].second << ' ';

    return 0;
}
