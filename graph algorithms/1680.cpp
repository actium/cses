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

std::vector<unsigned> solve(const graph_t& g, const graph_t& h)
{
    const unsigned n = g.size();

    std::vector<unsigned> v(n), p;
    for (unsigned i = 1; i < n; ++i)
        sort(g, i, v, p);

    std::vector<unsigned> d(n), s(n);
    for (const unsigned u : p) {
        if (u != 1 && s[u] == 0)
            continue;

        for (const unsigned v : h[u]) {
            if (d[v] < d[u] + 1) {
                d[v] = d[u] + 1;
                s[v] = u;
            }
        }
    }

    std::vector<unsigned> q;
    if (s[n-1] != 0) {
        for (unsigned x = n-1; x != 0; x = s[x])
            q.push_back(x);
    }
    return q;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, m;
    std::cin >> n >> m;

    graph_t g(1+n), h(1+n);
    for (unsigned i = 0; i < m; ++i) {
        unsigned a, b;
        std::cin >> a >> b;

        g[b].push_back(a);
        h[a].push_back(b);
    }

    const std::vector<unsigned> p = solve(g, h);
    if (!p.empty()) {
        std::cout << p.size() << '\n';
        for (auto it = p.rbegin(); it != p.rend(); ++it)
            std::cout << *it << ' ';
    } else {
        std::cout << "IMPOSSIBLE" << '\n';
    }

    return 0;
}
