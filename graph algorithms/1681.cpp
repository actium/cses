#include <iostream>
#include <vector>

using graph_t = std::vector<std::vector<unsigned>>;

constexpr unsigned M = 1'000'000'007;

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

unsigned solve(const graph_t& g, const graph_t& h)
{
    const unsigned n = g.size();

    std::vector<unsigned> v(n), p;
    for (unsigned i = 1; i < n; ++i)
        sort(g, i, v, p);

    std::vector<unsigned> c(n);
    c[1] = 1;
    for (const unsigned u : p) {
        for (const unsigned v : h[u])
            c[v] = (c[v] + c[u]) % M;
    }
    return c[n-1];
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

    std::cout << solve(g, h) << '\n';

    return 0;
}
