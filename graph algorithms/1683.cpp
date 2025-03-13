#include <iostream>
#include <vector>

using graph_t = std::vector<std::vector<unsigned>>;

template <typename F>
void traverse(const graph_t& g, unsigned u, std::vector<bool>& v, F&& callback)
{
    v[u] = true;

    for (const unsigned x : g[u]) {
        if (!v[x])
            traverse(g, x, v, std::forward<F>(callback));
    }

    callback(u);
}

void solve(const graph_t& g, const graph_t& h)
{
    const unsigned n = g.size();

    std::vector<unsigned> q;
    {
        std::vector<bool> v(n);
        for (unsigned i = 0; i < n; ++i) {
            if (!v[i])
                traverse(g, i, v, [&q](unsigned x) { q.push_back(x); });
        }
    }

    std::vector<unsigned> c(n);
    unsigned k = 0;
    {
        std::vector<bool> v(n);
        for (auto it = q.rbegin(); it != q.rend(); ++it) {
            if (!v[*it])
                traverse(h, *it, v, [id = ++k, &c](unsigned x) { c[x] = id; });
        }
    }

    std::cout << k << '\n';
    for (const unsigned x : c)
        std::cout << x << ' ';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, m;
    std::cin >> n >> m;

    graph_t g(n), h(n);
    for (unsigned i = 0; i < m; ++i) {
        unsigned s, t;
        std::cin >> s >> t;

        g[s-1].push_back(t-1);
        h[t-1].push_back(s-1);
    }

    solve(g, h);

    return 0;
}
