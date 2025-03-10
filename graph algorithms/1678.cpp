#include <iostream>
#include <vector>

using graph_t = std::vector<std::vector<unsigned>>;

unsigned search(const graph_t& g, unsigned u, std::vector<unsigned>& v, std::vector<unsigned>& p)
{
    const unsigned n = g.size();

    if (v[u] == 0) {
        v[u] = 1;

        for (const unsigned x : g[u]) {
            const unsigned t = search(g, x, v, p);
            if (t < n)
                p.push_back(u);

            if (!p.empty())
                return u == t ? n : t;
        }

        v[u] = 2;
    }
    return v[u] == 2 ? n : u;
}

void solve(const graph_t& g)
{
    const unsigned n = g.size();

    std::vector<unsigned> v(n), p;
    for (unsigned i = 0; i < n; ++i) {
        search(g, i, v, p);

        if (!p.empty()) {
            std::cout << p.size() + 1 << '\n';

            for (auto it = p.rbegin(); it != p.rend(); ++it)
                std::cout << 1 + *it << ' ';
            std::cout << 1 + p.back() << '\n';

            return;
        }
    }

    std::cout << "IMPOSSIBLE" << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, m;
    std::cin >> n >> m;

    graph_t g(n);
    for (unsigned i = 0; i < m; ++i) {
        unsigned s, t;
        std::cin >> s >> t;

        g[s-1].push_back(t-1);
    }

    solve(g);

    return 0;
}
