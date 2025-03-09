#include <iostream>
#include <queue>
#include <vector>

#include <climits>

struct Edge {
    unsigned s;
    unsigned t;
    int w;
};

using graph_t = std::vector<std::vector<Edge>>;

bool search(const graph_t g, unsigned u, unsigned t, std::vector<bool>& v)
{
    if (u == t)
        return true;

    v[u] = true;

    for (const Edge& e : g[u]) {
        if (!v[e.t] && search(g, e.t, t, v))
            return true;
    }

    return false;
}

long long solve(unsigned n, const std::vector<Edge>& edges)
{
    graph_t g(1+n);
    for (const Edge& e : edges)
        g[e.s].push_back(e);

    std::vector<long long> d(1+n, LONG_LONG_MIN);
    std::vector<unsigned> h(1+n);

    std::queue<unsigned> q;
    std::vector<bool> p(1+n), r(1+n);

    const auto enqueue = [&](unsigned u, unsigned v, int w) {
        d[v] = d[u] + w;
        h[v] = h[u] + 1;

        if (!p[v]) {
            q.push(v);
            p[v] = true;
        }
    };

    const auto dequeue = [&] {
        const unsigned x = q.front();
        q.pop();
        p[x] = false;
        return x;
    };

    d[0] = 0;
    enqueue(0, 1, 0);
    while (!q.empty()) {
        const unsigned u = dequeue();

        for (const Edge& e : g[u]) {
            if (d[u] + e.w <= d[e.t] || r[e.t])
                continue;

            enqueue(u, e.t, e.w);

            if (h[e.t] > n && search(g, e.t, n, r))
                return -1;
        }
    }

    return d[n];
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, m;
    std::cin >> n >> m;

    std::vector<Edge> edges(m);
    for (unsigned i = 0; i < m; ++i)
        std::cin >> edges[i].s >> edges[i].t >> edges[i].w;

    std::cout << solve(n, edges) << '\n';

    return 0;
}
