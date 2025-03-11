#include <iostream>
#include <vector>

using graph_t = std::vector<std::vector<unsigned>>;

bool sort(const graph_t& g, unsigned u, std::vector<unsigned>& v, std::vector<unsigned>& p)
{
    if (v[u] == 0) {
        v[u] = 1;

        for (const unsigned x : g[u]) {
            if (!sort(g, x, v, p))
                return false;
        }
        p.push_back(u);

        v[u] = 2;
    }
    return v[u] == 2;
}

std::vector<unsigned> solve(const graph_t& g)
{
    const unsigned n = g.size();

    std::vector<unsigned> v(n), p;
    for (unsigned i = 1; i < n; ++i) {
        if (!sort(g, i, v, p))
            return {};
    }
    return p;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, m;
    std::cin >> n >> m;

    graph_t g(1+n);
    for (unsigned i = 0; i < m; ++i) {
        unsigned a, b;
        std::cin >> a >> b;

        g[b].push_back(a);
    }

    const std::vector<unsigned> p = solve(g);
    if (!p.empty()) {
        for (const unsigned x : p)
            std::cout << x << ' ';
    } else {
        std::cout << "IMPOSSIBLE" << '\n';
    }

    return 0;
}
