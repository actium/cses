#include <iostream>
#include <vector>

using graph_t = std::vector<std::vector<size_t>>;

void count(const graph_t& g, size_t u, std::vector<unsigned>& c)
{
    for (const size_t x : g[u]) {
        count(g, x, c);
        c[u] += c[x] + 1;
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    graph_t g(n);
    for (size_t i = 1; i < n; ++i) {
        unsigned p;
        std::cin >> p;

        g[p-1].push_back(i);
    }

    std::vector<unsigned> c(n);
    count(g, 0, c);

    for (size_t i = 0; i < n; ++i)
        std::cout << c[i] << ' ';

    return 0;
}
