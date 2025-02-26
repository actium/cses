#include <iostream>
#include <vector>

using graph_t = std::vector<std::vector<size_t>>;

void compute_diameter(const graph_t& g, size_t u, size_t p, std::vector<unsigned>& dp, unsigned& d)
{
    for (const size_t x : g[u]) {
        if (x == p)
            continue;

        compute_diameter(g, x, u, dp, d);

        d = std::max(d, dp[u] + dp[x] + 1);
        dp[u] = std::max(dp[u], dp[x] + 1);
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    graph_t g(n);
    for (size_t i = 1; i < n; ++i) {
        unsigned u, v;
        std::cin >> u >> v;

        g[u-1].push_back(v-1);
        g[v-1].push_back(u-1);
    }

    unsigned d = 0;
    {
        std::vector<unsigned> dp(n);
        compute_diameter(g, 0, 0, dp, d);
    }
    std::cout << d << '\n';

    return 0;
}
