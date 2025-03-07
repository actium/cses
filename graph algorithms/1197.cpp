#include <iostream>
#include <queue>
#include <vector>

struct Edge {
    unsigned s;
    unsigned t;
    int w;
};

void solve(unsigned n, const std::vector<Edge>& edges)
{
    std::vector<std::vector<Edge>> g(1+n);
    for (const Edge& e : edges)
        g[e.s].push_back(e);

    std::vector<long long> d(1+n);
    std::vector<unsigned> h(1+n), s(1+n);

    std::queue<unsigned> q;
    std::vector<bool> p(1+n);

    const auto enqueue = [&](unsigned u, unsigned v, int w) {
        d[v] = d[u] + w;
        h[v] = h[u] + 1;
        s[v] = u;

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

    const auto trace = [&](unsigned v) {
        std::vector<unsigned> path;
        std::vector<bool> seen(1+n);
        while (!seen[v]) {
            path.push_back(v);
            seen[v] = true;
            v = s[v];
        }

        std::vector<unsigned> c = { v };
        do {
            c.push_back(path.back());
            path.pop_back();
        } while (c.back() != v);

        return c;
    };

    for (unsigned i = 1; i <= n; ++i)
        enqueue(0, i, 0);

    while (!q.empty()) {
        const unsigned u = dequeue();

        for (const Edge& e : g[u]) {
            if (d[u] + e.w < d[e.t])
                enqueue(u, e.t, e.w);

            if (h[e.t] > n) {
                std::cout << "YES" << '\n';

                for (const unsigned x : trace(e.t))
                    std::cout << x << ' ';

                return;
            }
        }
    }

    std::cout << "NO" << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, m;
    std::cin >> n >> m;

    std::vector<Edge> edges(m);
    for (unsigned i = 0; i < m; ++i)
        std::cin >> edges[i].s >> edges[i].t >> edges[i].w;

    solve(n, edges);

    return 0;
}
